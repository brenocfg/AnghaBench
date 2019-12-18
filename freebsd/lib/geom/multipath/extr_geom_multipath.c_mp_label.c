#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  char uint8_t ;
typedef  scalar_t__ uint32_t ;
struct gctl_req {int dummy; } ;
struct g_multipath_metadata {int md_active_active; int /*<<< orphan*/  md_uuid; scalar_t__ md_sectorsize; scalar_t__ md_size; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  char* intmax_t ;

/* Variables and functions */
 char* G_MULTIPATH_MAGIC ; 
 int /*<<< orphan*/  G_MULTIPATH_VERSION ; 
 char* calloc (int,scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_close (int) ; 
 scalar_t__ g_get_mediasize (char const*) ; 
 scalar_t__ g_get_sectorsize (char const*) ; 
 int g_metadata_store (char const*,char*,scalar_t__) ; 
 int g_open (char const*,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,...) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  multipath_metadata_encode (struct g_multipath_metadata*,char*) ; 
 scalar_t__ pread (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  uuid_create (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ uuid_s_ok ; 
 int /*<<< orphan*/  uuid_to_string (int /*<<< orphan*/ *,char**,scalar_t__*) ; 

__attribute__((used)) static void
mp_label(struct gctl_req *req)
{
	struct g_multipath_metadata md;
	off_t disksize = 0, msize;
	uint8_t *sector, *rsector;
	char *ptr;
	uuid_t uuid;
	ssize_t secsize = 0, ssize;
	uint32_t status;
	const char *name, *name2, *mpname;
	int error, i, nargs, fd;

	nargs = gctl_get_int(req, "nargs");
	if (nargs < 2) {
		gctl_error(req, "wrong number of arguments.");
		return;
	}

	/*
	 * First, check each provider to make sure it's the same size.
	 * This also gets us our size and sectorsize for the metadata.
	 */
	for (i = 1; i < nargs; i++) {
		name = gctl_get_ascii(req, "arg%d", i);
		msize = g_get_mediasize(name);
		ssize = g_get_sectorsize(name);
		if (msize == 0 || ssize == 0) {
			gctl_error(req, "cannot get information about %s: %s.",
			    name, strerror(errno));
			return;
		}
		if (i == 1) {
			secsize = ssize;
			disksize = msize;
		} else {
			if (secsize != ssize) {
				gctl_error(req, "%s sector size %ju different.",
				    name, (intmax_t)ssize);
				return;
			}
			if (disksize != msize) {
				gctl_error(req, "%s media size %ju different.",
				    name, (intmax_t)msize);
				return;
			}
		}
		
	}

	/*
	 * Generate metadata.
	 */
	strlcpy(md.md_magic, G_MULTIPATH_MAGIC, sizeof(md.md_magic));
	md.md_version = G_MULTIPATH_VERSION;
	mpname = gctl_get_ascii(req, "arg0");
	strlcpy(md.md_name, mpname, sizeof(md.md_name));
	md.md_size = disksize;
	md.md_sectorsize = secsize;
	uuid_create(&uuid, &status);
	if (status != uuid_s_ok) {
		gctl_error(req, "cannot create a UUID.");
		return;
	}
	uuid_to_string(&uuid, &ptr, &status);
	if (status != uuid_s_ok) {
		gctl_error(req, "cannot stringify a UUID.");
		return;
	}
	strlcpy(md.md_uuid, ptr, sizeof (md.md_uuid));
	md.md_active_active = gctl_get_int(req, "active_active");
	if (gctl_get_int(req, "active_read"))
		md.md_active_active = 2;
	free(ptr);

	/*
	 * Allocate a sector to write as metadata.
	 */
	sector = calloc(1, secsize);
	if (sector == NULL) {
		gctl_error(req, "unable to allocate metadata buffer");
		return;
	}
	rsector = malloc(secsize);
	if (rsector == NULL) {
		gctl_error(req, "unable to allocate metadata buffer");
		goto done;
	}

	/*
	 * encode the metadata
	 */
	multipath_metadata_encode(&md, sector);

	/*
	 * Store metadata on the initial provider.
	 */
	name = gctl_get_ascii(req, "arg1");
	error = g_metadata_store(name, sector, secsize);
	if (error != 0) {
		gctl_error(req, "cannot store metadata on %s: %s.", name, strerror(error));
		goto done;
	}

	/*
	 * Now touch the rest of the providers to hint retaste.
	 */
	for (i = 2; i < nargs; i++) {
		name2 = gctl_get_ascii(req, "arg%d", i);
		fd = g_open(name2, 1);
		if (fd < 0) {
			fprintf(stderr, "Unable to open %s: %s.\n",
			    name2, strerror(errno));
			continue;
		}
		if (pread(fd, rsector, secsize, disksize - secsize) !=
		    (ssize_t)secsize) {
			fprintf(stderr, "Unable to read metadata from %s: %s.\n",
			    name2, strerror(errno));
			g_close(fd);
			continue;
		}
		g_close(fd);
		if (memcmp(sector, rsector, secsize)) {
			fprintf(stderr, "No metadata found on %s."
			    " It is not a path of %s.\n",
			    name2, name);
		}
	}
done:
	free(rsector);
	free(sector);
}
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
typedef  int uint64_t ;
struct gctl_req {int dummy; } ;
struct g_eli_metadata {int md_provsize; scalar_t__ md_version; } ;
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
#define  EINVAL 129 
#define  EOPNOTSUPP 128 
 int /*<<< orphan*/  G_ELI_VERSION ; 
 int eli_metadata_decode (unsigned char*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  eli_metadata_store (struct gctl_req*,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  eli_trash_metadata (struct gctl_req*,char const*,int,int) ; 
 int errno ; 
 int /*<<< orphan*/  explicit_bzero (unsigned char*,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  g_close (int) ; 
 int g_mediasize (int) ; 
 int g_open (char const*,int) ; 
 int g_sectorsize (int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_ascii (struct gctl_req*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int gctl_get_intmax (struct gctl_req*,char*) ; 
 unsigned char* malloc (int) ; 
 int pread (int,unsigned char*,int,int) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void
eli_resize(struct gctl_req *req)
{
	struct g_eli_metadata md;
	const char *prov;
	unsigned char *sector;
	ssize_t secsize;
	off_t mediasize, oldsize;
	int error, nargs, provfd;

	nargs = gctl_get_int(req, "nargs");
	if (nargs != 1) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}
	prov = gctl_get_ascii(req, "arg0");

	provfd = -1;
	sector = NULL;
	secsize = 0;

	provfd = g_open(prov, 1);
	if (provfd == -1) {
		gctl_error(req, "Cannot open %s: %s.", prov, strerror(errno));
		goto out;
	}

	mediasize = g_mediasize(provfd);
	secsize = g_sectorsize(provfd);
	if (mediasize == -1 || secsize == -1) {
		gctl_error(req, "Cannot get information about %s: %s.", prov,
		    strerror(errno));
		goto out;
	}

	sector = malloc(secsize);
	if (sector == NULL) {
		gctl_error(req, "Cannot allocate memory.");
		goto out;
	}

	oldsize = gctl_get_intmax(req, "oldsize");
	if (oldsize < 0 || oldsize > mediasize) {
		gctl_error(req, "Invalid oldsize: Out of range.");
		goto out;
	}
	if (oldsize == mediasize) {
		gctl_error(req, "Size hasn't changed.");
		goto out;
	}

	/* Read metadata from the 'oldsize' offset. */
	if (pread(provfd, sector, secsize, oldsize - secsize) != secsize) {
		gctl_error(req, "Cannot read old metadata: %s.",
		    strerror(errno));
		goto out;
	}

	/* Check if this sector contains geli metadata. */
	error = eli_metadata_decode(sector, &md);
	switch (error) {
	case 0:
		break;
	case EOPNOTSUPP:
		gctl_error(req,
		    "Provider's %s metadata version %u is too new.\n"
		    "geli: The highest supported version is %u.",
		    prov, (unsigned int)md.md_version, G_ELI_VERSION);
		goto out;
	case EINVAL:
		gctl_error(req, "Inconsistent provider's %s metadata.", prov);
		goto out;
	default:
		gctl_error(req,
		    "Unexpected error while decoding provider's %s metadata: %s.",
		    prov, strerror(error));
		goto out;
	}

	/*
	 * If the old metadata doesn't have a correct provider size, refuse
	 * to resize.
	 */
	if (md.md_provsize != (uint64_t)oldsize) {
		gctl_error(req, "Provider size mismatch at oldsize.");
		goto out;
	}

	/*
	 * Update the old metadata with the current provider size and write
	 * it back to the correct place on the provider.
	 */
	md.md_provsize = mediasize;
	/* Write metadata to the provider. */
	(void)eli_metadata_store(req, prov, &md);
	/* Now trash the old metadata. */
	(void)eli_trash_metadata(req, prov, provfd, oldsize - secsize);
out:
	if (provfd != -1)
		(void)g_close(provfd);
	if (sector != NULL) {
		explicit_bzero(sector, secsize);
		free(sector);
	}
}
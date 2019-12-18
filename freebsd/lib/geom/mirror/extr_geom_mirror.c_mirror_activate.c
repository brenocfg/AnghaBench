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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  tmpmd ;
struct gctl_req {int dummy; } ;
struct g_mirror_metadata {int /*<<< orphan*/  md_dflags; int /*<<< orphan*/  md_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DISK_FLAG_INACTIVE ; 
 int /*<<< orphan*/  G_MIRROR_MAGIC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int g_metadata_read (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int g_metadata_store (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,...) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 scalar_t__ mirror_metadata_decode (int /*<<< orphan*/ *,struct g_mirror_metadata*) ; 
 int /*<<< orphan*/  mirror_metadata_encode (struct g_mirror_metadata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strerror (int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
mirror_activate(struct gctl_req *req)
{
	struct g_mirror_metadata md, tmpmd;
	const char *name, *path;
	int error, i, nargs;

	nargs = gctl_get_int(req, "nargs");
	if (nargs < 2) {
		gctl_error(req, "Too few arguments.");
		return;
	}
	name = gctl_get_ascii(req, "arg0");

	for (i = 1; i < nargs; i++) {
		path = gctl_get_ascii(req, "arg%d", i);
		error = g_metadata_read(path, (u_char *)&tmpmd, sizeof(tmpmd),
		    G_MIRROR_MAGIC);
		if (error != 0) {
			fprintf(stderr, "Cannot read metadata from %s: %s.\n",
			    path, strerror(error));
			gctl_error(req, "Not fully done.");
			continue;
		}
		if (mirror_metadata_decode((u_char *)&tmpmd, &md) != 0) {
			fprintf(stderr,
			    "MD5 hash mismatch for provider %s, skipping.\n",
			    path);
			gctl_error(req, "Not fully done.");
			continue;
		}
		if (strcmp(md.md_name, name) != 0) {
			fprintf(stderr,
			    "Provider %s is not the mirror %s component.\n",
			    path, name);
			gctl_error(req, "Not fully done.");
			continue;
		}
		md.md_dflags &= ~G_MIRROR_DISK_FLAG_INACTIVE;
		mirror_metadata_encode(&md, (u_char *)&tmpmd);
		error = g_metadata_store(path, (u_char *)&tmpmd, sizeof(tmpmd));
		if (error != 0) {
			fprintf(stderr, "Cannot write metadata from %s: %s.\n",
			    path, strerror(error));
			gctl_error(req, "Not fully done.");
			continue;
		}
		if (verbose)
			printf("Provider %s activated.\n", path);
	}
}
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
typedef  scalar_t__ uint64_t ;
struct gctl_req {int dummy; } ;
struct g_eli_metadata {scalar_t__ md_provsize; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int eli_metadata_read (struct gctl_req*,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  eli_metadata_store (struct gctl_req*,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ g_get_mediasize (char const*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_ascii (struct gctl_req*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eli_restore(struct gctl_req *req)
{
	struct g_eli_metadata md;
	const char *file, *prov;
	off_t mediasize;
	int nargs;

	nargs = gctl_get_int(req, "nargs");
	if (nargs != 2) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}
	file = gctl_get_ascii(req, "arg0");
	prov = gctl_get_ascii(req, "arg1");

	/* Read metadata from the backup file. */
	if (eli_metadata_read(req, file, &md) == -1)
		return;
	/* Obtain provider's mediasize. */
	mediasize = g_get_mediasize(prov);
	if (mediasize == 0) {
		gctl_error(req, "Cannot get informations about %s: %s.", prov,
		    strerror(errno));
		return;
	}
	/* Check if the provider size has changed since we did the backup. */
	if (md.md_provsize != (uint64_t)mediasize) {
		if (gctl_get_int(req, "force")) {
			md.md_provsize = mediasize;
		} else {
			gctl_error(req, "Provider size mismatch: "
			    "wrong backup file?");
			return;
		}
	}
	/* Write metadata to the provider. */
	(void)eli_metadata_store(req, prov, &md);
}
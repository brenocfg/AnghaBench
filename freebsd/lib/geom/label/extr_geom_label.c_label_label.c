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
struct gctl_req {int dummy; } ;
struct g_label_metadata {scalar_t__ md_provsize; int /*<<< orphan*/ * md_label; int /*<<< orphan*/  md_version; int /*<<< orphan*/ * md_magic; } ;
typedef  int /*<<< orphan*/  sector ;

/* Variables and functions */
 char const* G_LABEL_MAGIC ; 
 int /*<<< orphan*/  G_LABEL_VERSION ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ g_get_mediasize (char const*) ; 
 int g_metadata_clear (char const*,int /*<<< orphan*/ *) ; 
 int g_metadata_store (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_ascii (struct gctl_req*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  label_metadata_encode (struct g_label_metadata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
label_label(struct gctl_req *req)
{
	struct g_label_metadata md;
	const char *name, *label;
	u_char sector[512];
	int error, nargs;

	bzero(sector, sizeof(sector));
	nargs = gctl_get_int(req, "nargs");
	if (nargs != 2) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}

	/*
	 * Clear last sector first to spoil all components if device exists.
	 */
	name = gctl_get_ascii(req, "arg1");
	error = g_metadata_clear(name, NULL);
	if (error != 0) {
		gctl_error(req, "Can't store metadata on %s: %s.", name,
		    strerror(error));
		return;
	}

	strlcpy(md.md_magic, G_LABEL_MAGIC, sizeof(md.md_magic));
	md.md_version = G_LABEL_VERSION;
	label = gctl_get_ascii(req, "arg0");
	bzero(md.md_label, sizeof(md.md_label));
	strlcpy(md.md_label, label, sizeof(md.md_label));
	md.md_provsize = g_get_mediasize(name);
	if (md.md_provsize == 0) {
		gctl_error(req, "Can't get mediasize of %s: %s.", name,
		    strerror(errno));
		return;
	}

	/*
	 * Ok, store metadata.
	 */
	label_metadata_encode(&md, sector);
	error = g_metadata_store(name, sector, sizeof(sector));
	if (error != 0) {
		fprintf(stderr, "Can't store metadata on %s: %s.\n", name,
		    strerror(error));
		gctl_error(req, "Not done.");
	}
	if (verbose)
		printf("Metadata value stored on %s.\n", name);
}
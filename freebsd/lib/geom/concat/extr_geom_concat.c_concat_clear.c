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
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_CONCAT_MAGIC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int g_metadata_clear (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,int) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
concat_clear(struct gctl_req *req)
{
	const char *name;
	int error, i, nargs;

	nargs = gctl_get_int(req, "nargs");
	if (nargs < 1) {
		gctl_error(req, "Too few arguments.");
		return;
	}

	for (i = 0; i < nargs; i++) {
		name = gctl_get_ascii(req, "arg%d", i);
		error = g_metadata_clear(name, G_CONCAT_MAGIC);
		if (error != 0) {
			fprintf(stderr, "Can't clear metadata on %s: %s.\n",
			    name, strerror(error));
			gctl_error(req, "Not fully done.");
			continue;
		}
		if (verbose)
			printf("Metadata cleared on %s.\n", name);
	}
}
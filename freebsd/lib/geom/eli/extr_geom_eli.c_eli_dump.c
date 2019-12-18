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
struct g_eli_metadata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eli_metadata_dump (struct g_eli_metadata*) ; 
 int eli_metadata_read (int /*<<< orphan*/ *,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,int) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
eli_dump(struct gctl_req *req)
{
	struct g_eli_metadata md;
	const char *name;
	int i, nargs;

	nargs = gctl_get_int(req, "nargs");
	if (nargs < 1) {
		gctl_error(req, "Too few arguments.");
		return;
	}

	for (i = 0; i < nargs; i++) {
		name = gctl_get_ascii(req, "arg%d", i);
		if (eli_metadata_read(NULL, name, &md) == -1) {
			gctl_error(req, "Not fully done.");
			continue;
		}
		printf("Metadata on %s:\n", name);
		eli_metadata_dump(&md);
		printf("\n");
	}
}
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
struct g_virstor_metadata {int dummy; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  md ;

/* Variables and functions */
 int /*<<< orphan*/  G_VIRSTOR_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int g_metadata_read (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  virstor_metadata_decode (int /*<<< orphan*/ *,struct g_virstor_metadata*) ; 
 int /*<<< orphan*/  virstor_metadata_dump (struct g_virstor_metadata*) ; 

__attribute__((used)) static void
virstor_dump(struct gctl_req *req)
{
	struct g_virstor_metadata md;
	u_char tmpmd[512];	/* temporary buffer */
	const char *name;
	char param[16];
	int nargs, error, i;

	assert(sizeof(tmpmd) >= sizeof(md));

	nargs = gctl_get_int(req, "nargs");
	if (nargs < 1) {
		gctl_error(req, "Too few arguments.");
		return;
	}
	for (i = 0; i < nargs; i++) {
		snprintf(param, sizeof(param), "arg%u", i);
		name = gctl_get_ascii(req, "%s", param);

		error = g_metadata_read(name, (u_char *) & tmpmd, sizeof(tmpmd),
		    G_VIRSTOR_MAGIC);
		if (error != 0) {
			fprintf(stderr, "Can't read metadata from %s: %s.\n",
			    name, strerror(error));
			gctl_error(req,
			    "Not fully done (error reading metadata).");
			continue;
		}
		virstor_metadata_decode((u_char *) & tmpmd, &md);
		printf("Metadata on %s:\n", name);
		virstor_metadata_dump(&md);
		printf("\n");
	}
}
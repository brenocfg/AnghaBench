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
struct g_cache_metadata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_CACHE_MAGIC ; 
 int /*<<< orphan*/  cache_metadata_decode (int /*<<< orphan*/ *,struct g_cache_metadata*) ; 
 int /*<<< orphan*/  cache_metadata_dump (struct g_cache_metadata*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int g_metadata_read (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,int) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static void
cache_dump(struct gctl_req *req)
{
	struct g_cache_metadata md, tmpmd;
	const char *name;
	int error, i, nargs;

	nargs = gctl_get_int(req, "nargs");
	if (nargs < 1) {
		gctl_error(req, "Too few arguments.");
		return;
	}

	for (i = 0; i < nargs; i++) {
		name = gctl_get_ascii(req, "arg%d", i);
		error = g_metadata_read(name, (u_char *)&tmpmd, sizeof(tmpmd),
		    G_CACHE_MAGIC);
		if (error != 0) {
			fprintf(stderr, "Can't read metadata from %s: %s.\n",
			    name, strerror(error));
			gctl_error(req, "Not fully done.");
			continue;
		}
		cache_metadata_decode((u_char *)&tmpmd, &md);
		printf("Metadata on %s:\n", name);
		cache_metadata_dump(&md);
		printf("\n");
	}
}
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
struct gmesh {int dummy; } ;
struct ggeom {int /*<<< orphan*/  lg_name; } ;
struct gctl_req {int dummy; } ;
struct gclass {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* GPART_PARAM_BOOTCODE ; 
 char* GPART_PARAM_INDEX ; 
 char* GPART_PARAM_PARTCODE ; 
 size_t VTOC_BOOTSIZE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 struct gclass* find_class (struct gmesh*,char const*) ; 
 struct ggeom* find_geom (struct gclass*,char const*) ; 
 char* find_geomcfg (struct ggeom*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int gctl_change_param (struct gctl_req*,char*,size_t,void*) ; 
 int gctl_delete_param (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 scalar_t__ gctl_get_intmax (struct gctl_req*,char*) ; 
 scalar_t__ gctl_has_param (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  geom_deletetree (struct gmesh*) ; 
 int geom_gettree (struct gmesh*) ; 
 void* gpart_bootfile_read (char const*,size_t*) ; 
 int /*<<< orphan*/  gpart_issue (struct gctl_req*,unsigned int) ; 
 int /*<<< orphan*/  gpart_write_partcode (struct ggeom*,int,void*,size_t) ; 
 int /*<<< orphan*/  gpart_write_partcode_vtoc8 (struct ggeom*,int,void*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
gpart_bootcode(struct gctl_req *req, unsigned int fl)
{
	struct gmesh mesh;
	struct gclass *classp;
	struct ggeom *gp;
	const char *s;
	void *bootcode, *partcode;
	size_t bootsize, partsize;
	int error, idx, vtoc8;

	if (gctl_has_param(req, GPART_PARAM_BOOTCODE)) {
		s = gctl_get_ascii(req, GPART_PARAM_BOOTCODE);
		bootsize = 800 * 1024;		/* Arbitrary limit. */
		bootcode = gpart_bootfile_read(s, &bootsize);
		error = gctl_change_param(req, GPART_PARAM_BOOTCODE, bootsize,
		    bootcode);
		if (error)
			errc(EXIT_FAILURE, error, "internal error");
	} else
		bootcode = NULL;

	s = gctl_get_ascii(req, "class");
	if (s == NULL)
		abort();
	error = geom_gettree(&mesh);
	if (error != 0)
		errc(EXIT_FAILURE, error, "Cannot get GEOM tree");
	classp = find_class(&mesh, s);
	if (classp == NULL) {
		geom_deletetree(&mesh);
		errx(EXIT_FAILURE, "Class %s not found.", s);
	}
	if (gctl_get_int(req, "nargs") != 1)
		errx(EXIT_FAILURE, "Invalid number of arguments.");
	s = gctl_get_ascii(req, "arg0");
	if (s == NULL)
		abort();
	gp = find_geom(classp, s);
	if (gp == NULL)
		errx(EXIT_FAILURE, "No such geom: %s.", s);
	s = find_geomcfg(gp, "scheme");
	if (s == NULL)
		errx(EXIT_FAILURE, "Scheme not found for geom %s", gp->lg_name);
	if (strcmp(s, "VTOC8") == 0)
		vtoc8 = 1;
	else
		vtoc8 = 0;

	if (gctl_has_param(req, GPART_PARAM_PARTCODE)) {
		s = gctl_get_ascii(req, GPART_PARAM_PARTCODE);
		if (vtoc8 != 0)
			partsize = VTOC_BOOTSIZE;
		else
			partsize = 1024 * 1024;		/* Arbitrary limit. */
		partcode = gpart_bootfile_read(s, &partsize);
		error = gctl_delete_param(req, GPART_PARAM_PARTCODE);
		if (error)
			errc(EXIT_FAILURE, error, "internal error");
	} else
		partcode = NULL;

	if (gctl_has_param(req, GPART_PARAM_INDEX)) {
		if (partcode == NULL)
			errx(EXIT_FAILURE, "-i is only valid with -p");
		idx = (int)gctl_get_intmax(req, GPART_PARAM_INDEX);
		if (idx < 1)
			errx(EXIT_FAILURE, "invalid partition index");
		error = gctl_delete_param(req, GPART_PARAM_INDEX);
		if (error)
			errc(EXIT_FAILURE, error, "internal error");
	} else
		idx = 0;

	if (partcode != NULL) {
		if (vtoc8 == 0) {
			if (idx == 0)
				errx(EXIT_FAILURE, "missing -i option");
			gpart_write_partcode(gp, idx, partcode, partsize);
		} else {
			if (partsize != VTOC_BOOTSIZE)
				errx(EXIT_FAILURE, "invalid bootcode");
			gpart_write_partcode_vtoc8(gp, idx, partcode);
		}
	} else
		if (bootcode == NULL)
			errx(EXIT_FAILURE, "no -b nor -p");

	if (bootcode != NULL)
		gpart_issue(req, fl);

	geom_deletetree(&mesh);
	free(partcode);
}
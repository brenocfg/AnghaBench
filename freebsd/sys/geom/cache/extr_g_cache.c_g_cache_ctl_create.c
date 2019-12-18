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
typedef  int u_int ;
struct gctl_req {int dummy; } ;
struct g_provider {int dummy; } ;
struct g_geom {int dummy; } ;
struct g_class {int dummy; } ;
struct g_cache_metadata {char const* md_magic; char const* md_name; int md_size; int md_bsize; scalar_t__ md_provsize; int /*<<< orphan*/  md_version; } ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_CACHE_DEBUG (int,char*,char const*) ; 
 char const* G_CACHE_MAGIC ; 
 int /*<<< orphan*/  G_CACHE_TYPE_MANUAL ; 
 int /*<<< orphan*/  G_CACHE_VERSION ; 
 struct g_geom* g_cache_create (struct g_class*,struct g_provider*,struct g_cache_metadata*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 void* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char const*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_cache_ctl_create(struct gctl_req *req, struct g_class *mp)
{
	struct g_cache_metadata md;
	struct g_provider *pp;
	struct g_geom *gp;
	intmax_t *bsize, *size;
	const char *name;
	int *nargs;

	g_topology_assert();

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument", "nargs");
		return;
	}
	if (*nargs != 2) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}

	strlcpy(md.md_magic, G_CACHE_MAGIC, sizeof(md.md_magic));
	md.md_version = G_CACHE_VERSION;
	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg0' argument");
		return;
	}
	strlcpy(md.md_name, name, sizeof(md.md_name));

	size = gctl_get_paraml(req, "size", sizeof(*size));
	if (size == NULL) {
		gctl_error(req, "No '%s' argument", "size");
		return;
	}
	if ((u_int)*size < 100) {
		gctl_error(req, "Invalid '%s' argument", "size");
		return;
	}
	md.md_size = (u_int)*size;

	bsize = gctl_get_paraml(req, "blocksize", sizeof(*bsize));
	if (bsize == NULL) {
		gctl_error(req, "No '%s' argument", "blocksize");
		return;
	}
	if (*bsize < 0) {
		gctl_error(req, "Invalid '%s' argument", "blocksize");
		return;
	}
	md.md_bsize = (u_int)*bsize;

	/* This field is not important here. */
	md.md_provsize = 0;

	name = gctl_get_asciiparam(req, "arg1");
	if (name == NULL) {
		gctl_error(req, "No 'arg1' argument");
		return;
	}
	if (strncmp(name, "/dev/", strlen("/dev/")) == 0)
		name += strlen("/dev/");
	pp = g_provider_by_name(name);
	if (pp == NULL) {
		G_CACHE_DEBUG(1, "Provider %s is invalid.", name);
		gctl_error(req, "Provider %s is invalid.", name);
		return;
	}
	gp = g_cache_create(mp, pp, &md, G_CACHE_TYPE_MANUAL);
	if (gp == NULL) {
		gctl_error(req, "Can't create %s.", md.md_name);
		return;
	}
}
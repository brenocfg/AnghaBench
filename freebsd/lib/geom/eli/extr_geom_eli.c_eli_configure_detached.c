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
struct g_eli_metadata {int md_flags; } ;
typedef  int /*<<< orphan*/  md ;

/* Variables and functions */
 int G_ELI_FLAG_AUTORESIZE ; 
 int G_ELI_FLAG_BOOT ; 
 int G_ELI_FLAG_GELIBOOT ; 
 int G_ELI_FLAG_GELIDISPLAYPASS ; 
 int G_ELI_FLAG_NODELETE ; 
 int eli_metadata_read (struct gctl_req*,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  eli_metadata_store (struct gctl_req*,char const*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  explicit_bzero (struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
eli_configure_detached(struct gctl_req *req, const char *prov, int boot,
    int geliboot, int displaypass, int trim, int autoresize)
{
	struct g_eli_metadata md;
	bool changed = 0;

	if (eli_metadata_read(req, prov, &md) == -1)
		return;

	if (boot == 1 && (md.md_flags & G_ELI_FLAG_BOOT)) {
		if (verbose)
			printf("BOOT flag already configured for %s.\n", prov);
	} else if (boot == 0 && !(md.md_flags & G_ELI_FLAG_BOOT)) {
		if (verbose)
			printf("BOOT flag not configured for %s.\n", prov);
	} else if (boot >= 0) {
		if (boot)
			md.md_flags |= G_ELI_FLAG_BOOT;
		else
			md.md_flags &= ~G_ELI_FLAG_BOOT;
		changed = 1;
	}

	if (geliboot == 1 && (md.md_flags & G_ELI_FLAG_GELIBOOT)) {
		if (verbose)
			printf("GELIBOOT flag already configured for %s.\n", prov);
	} else if (geliboot == 0 && !(md.md_flags & G_ELI_FLAG_GELIBOOT)) {
		if (verbose)
			printf("GELIBOOT flag not configured for %s.\n", prov);
	} else if (geliboot >= 0) {
		if (geliboot)
			md.md_flags |= G_ELI_FLAG_GELIBOOT;
		else
			md.md_flags &= ~G_ELI_FLAG_GELIBOOT;
		changed = 1;
	}

	if (displaypass == 1 && (md.md_flags & G_ELI_FLAG_GELIDISPLAYPASS)) {
		if (verbose)
			printf("GELIDISPLAYPASS flag already configured for %s.\n", prov);
	} else if (displaypass == 0 &&
	    !(md.md_flags & G_ELI_FLAG_GELIDISPLAYPASS)) {
		if (verbose)
			printf("GELIDISPLAYPASS flag not configured for %s.\n", prov);
	} else if (displaypass >= 0) {
		if (displaypass)
			md.md_flags |= G_ELI_FLAG_GELIDISPLAYPASS;
		else
			md.md_flags &= ~G_ELI_FLAG_GELIDISPLAYPASS;
		changed = 1;
	}

	if (trim == 0 && (md.md_flags & G_ELI_FLAG_NODELETE)) {
		if (verbose)
			printf("TRIM disable flag already configured for %s.\n", prov);
	} else if (trim == 1 && !(md.md_flags & G_ELI_FLAG_NODELETE)) {
		if (verbose)
			printf("TRIM disable flag not configured for %s.\n", prov);
	} else if (trim >= 0) {
		if (trim)
			md.md_flags &= ~G_ELI_FLAG_NODELETE;
		else
			md.md_flags |= G_ELI_FLAG_NODELETE;
		changed = 1;
	}

	if (autoresize == 1 && (md.md_flags & G_ELI_FLAG_AUTORESIZE)) {
		if (verbose)
			printf("AUTORESIZE flag already configured for %s.\n", prov);
	} else if (autoresize == 0 && !(md.md_flags & G_ELI_FLAG_AUTORESIZE)) {
		if (verbose)
			printf("AUTORESIZE flag not configured for %s.\n", prov);
	} else if (autoresize >= 0) {
		if (autoresize)
			md.md_flags |= G_ELI_FLAG_AUTORESIZE;
		else
			md.md_flags &= ~G_ELI_FLAG_AUTORESIZE;
		changed = 1;
	}

	if (changed)
		eli_metadata_store(req, prov, &md);
	explicit_bzero(&md, sizeof(md));
}
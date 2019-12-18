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
struct g_provider {int /*<<< orphan*/  sectorsize; } ;
struct g_geom {void* spoiled; void* orphan; int /*<<< orphan*/  access; int /*<<< orphan*/  start; } ;
struct g_eli_metadata {int dummy; } ;
struct g_consumer {int acr; int /*<<< orphan*/ * provider; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int eli_metadata_decode (int /*<<< orphan*/ *,struct g_eli_metadata*) ; 
 int g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 void* g_eli_orphan_spoil_assert ; 
 int /*<<< orphan*/  g_eli_start ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*) ; 
 int /*<<< orphan*/ * g_read_data (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  g_std_access ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 

__attribute__((used)) static int
g_eli_read_metadata_offset(struct g_class *mp, struct g_provider *pp,
    off_t offset, struct g_eli_metadata *md)
{
	struct g_geom *gp;
	struct g_consumer *cp;
	u_char *buf = NULL;
	int error;

	g_topology_assert();

	gp = g_new_geomf(mp, "eli:taste");
	gp->start = g_eli_start;
	gp->access = g_std_access;
	/*
	 * g_eli_read_metadata() is always called from the event thread.
	 * Our geom is created and destroyed in the same event, so there
	 * could be no orphan nor spoil event in the meantime.
	 */
	gp->orphan = g_eli_orphan_spoil_assert;
	gp->spoiled = g_eli_orphan_spoil_assert;
	cp = g_new_consumer(gp);
	error = g_attach(cp, pp);
	if (error != 0)
		goto end;
	error = g_access(cp, 1, 0, 0);
	if (error != 0)
		goto end;
	g_topology_unlock();
	buf = g_read_data(cp, offset, pp->sectorsize, &error);
	g_topology_lock();
	if (buf == NULL)
		goto end;
	error = eli_metadata_decode(buf, md);
	if (error != 0)
		goto end;
	/* Metadata was read and decoded successfully. */
end:
	if (buf != NULL)
		g_free(buf);
	if (cp->provider != NULL) {
		if (cp->acr == 1)
			g_access(cp, -1, 0, 0);
		g_detach(cp);
	}
	g_destroy_consumer(cp);
	g_destroy_geom(gp);
	return (error);
}
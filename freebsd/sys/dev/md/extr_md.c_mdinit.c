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
struct md_s {int type; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  unit; int /*<<< orphan*/  devstat; struct g_provider* pp; struct g_geom* gp; int /*<<< orphan*/  mediasize; } ;
struct g_provider {int flags; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; } ;
struct g_geom {struct md_s* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVSTAT_ALL_SUPPORTED ; 
 int /*<<< orphan*/  DEVSTAT_PRIORITY_MAX ; 
 int /*<<< orphan*/  DEVSTAT_TYPE_DIRECT ; 
 int G_PF_ACCEPT_UNMAPPED ; 
 int G_PF_DIRECT_RECEIVE ; 
 int G_PF_DIRECT_SEND ; 
#define  MD_MALLOC 132 
#define  MD_NULL 131 
#define  MD_PRELOAD 130 
#define  MD_SWAP 129 
#define  MD_VNODE 128 
 int /*<<< orphan*/  devstat_new_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_md_class ; 
 struct g_geom* g_new_geomf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_new_providerf (struct g_geom*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 

__attribute__((used)) static void
mdinit(struct md_s *sc)
{
	struct g_geom *gp;
	struct g_provider *pp;

	g_topology_lock();
	gp = g_new_geomf(&g_md_class, "md%d", sc->unit);
	gp->softc = sc;
	pp = g_new_providerf(gp, "md%d", sc->unit);
	pp->flags |= G_PF_DIRECT_SEND | G_PF_DIRECT_RECEIVE;
	pp->mediasize = sc->mediasize;
	pp->sectorsize = sc->sectorsize;
	switch (sc->type) {
	case MD_MALLOC:
	case MD_VNODE:
	case MD_SWAP:
		pp->flags |= G_PF_ACCEPT_UNMAPPED;
		break;
	case MD_PRELOAD:
	case MD_NULL:
		break;
	}
	sc->gp = gp;
	sc->pp = pp;
	g_error_provider(pp, 0);
	g_topology_unlock();
	sc->devstat = devstat_new_entry("md", sc->unit, sc->sectorsize,
	    DEVSTAT_ALL_SUPPORTED, DEVSTAT_TYPE_DIRECT, DEVSTAT_PRIORITY_MAX);
}
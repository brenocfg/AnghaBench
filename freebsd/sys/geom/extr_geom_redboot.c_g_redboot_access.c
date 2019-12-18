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
struct g_slicer {struct g_redboot_softc* softc; } ;
struct g_redboot_softc {int (* parent_access ) (struct g_provider*,int,int,int) ;scalar_t__* readonly; } ;
struct g_provider {size_t index; struct g_geom* geom; } ;
struct g_geom {struct g_slicer* softc; } ;

/* Variables and functions */
 int EPERM ; 
 int stub1 (struct g_provider*,int,int,int) ; 

__attribute__((used)) static int
g_redboot_access(struct g_provider *pp, int dread, int dwrite, int dexcl)
{
	struct g_geom *gp = pp->geom;
	struct g_slicer *gsp = gp->softc;
	struct g_redboot_softc *sc = gsp->softc;

	if (dwrite > 0 && sc->readonly[pp->index])
		return (EPERM);
	return (sc->parent_access(pp, dread, dwrite, dexcl));
}
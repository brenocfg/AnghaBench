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
struct g_provider {scalar_t__ acr; scalar_t__ acw; scalar_t__ ace; } ;
struct g_geom {struct ccd_s* softc; int /*<<< orphan*/  name; int /*<<< orphan*/  provider; } ;
struct g_class {int dummy; } ;
struct ccd_s {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ENXIO ; 
 struct g_provider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_ccd_freesc (struct ccd_s*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
g_ccd_destroy_geom(struct gctl_req *req, struct g_class *mp, struct g_geom *gp)
{
	struct g_provider *pp;
	struct ccd_s *sc;

	g_topology_assert();
	sc = gp->softc;
	pp = LIST_FIRST(&gp->provider);
	if (sc == NULL || pp == NULL)
		return (EBUSY);
	if (pp->acr != 0 || pp->acw != 0 || pp->ace != 0) {
		gctl_error(req, "%s is open(r%dw%de%d)", gp->name,
		    pp->acr, pp->acw, pp->ace);
		return (EBUSY);
	}
	g_ccd_freesc(sc);
	gp->softc = NULL;
	g_wither_geom(gp, ENXIO);
	return (0);
}
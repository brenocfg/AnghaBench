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
typedef  scalar_t__ u_int ;
struct chipc_softc {int /*<<< orphan*/  mem_regions; int /*<<< orphan*/  mem_rman; int /*<<< orphan*/  dev; } ;
struct chipc_region {scalar_t__ cr_rid; int /*<<< orphan*/  cr_end; int /*<<< orphan*/  cr_addr; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_DEBUG_DEV (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int ENODEV ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct chipc_region*,int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_get_region_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bhnd_port_type_name (int /*<<< orphan*/ ) ; 
 struct chipc_region* chipc_alloc_region (struct chipc_softc*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  chipc_free_region (struct chipc_softc*,struct chipc_region*) ; 
 int /*<<< orphan*/  cr_link ; 
 int rman_manage_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_rman_init_regions (struct chipc_softc *sc, bhnd_port_type type,
    u_int port)
{
	struct	chipc_region	*cr;
	rman_res_t		 start, end;
	u_int			 num_regions;
	int			 error;

	num_regions = bhnd_get_region_count(sc->dev, type, port);
	for (u_int region = 0; region < num_regions; region++) {
		/* Allocate new region record */
		cr = chipc_alloc_region(sc, type, port, region);
		if (cr == NULL)
			return (ENODEV);

		/* Can't manage regions that cannot be allocated */
		if (cr->cr_rid < 0) {
			BHND_DEBUG_DEV(sc->dev, "no rid for chipc region "
			    "%s%u.%u", bhnd_port_type_name(type), port, region);
			chipc_free_region(sc, cr);
			continue;
		}

		/* Add to rman's managed range */
		start = cr->cr_addr;
		end = cr->cr_end;
		if ((error = rman_manage_region(&sc->mem_rman, start, end))) {
			chipc_free_region(sc, cr);
			return (error);
		}

		/* Add to region list */
		STAILQ_INSERT_TAIL(&sc->mem_regions, cr, cr_link);
	}

	return (0);
}
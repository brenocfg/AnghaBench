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
struct chipc_softc {int /*<<< orphan*/  dev; } ;
struct chipc_region {scalar_t__ cr_refs; int cr_res_rid; int cr_rid; scalar_t__ cr_act_refs; int /*<<< orphan*/ * cr_res; int /*<<< orphan*/  cr_count; int /*<<< orphan*/  cr_end; int /*<<< orphan*/  cr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPC_LOCK (struct chipc_softc*) ; 
 int /*<<< orphan*/  CHIPC_UNLOCK (struct chipc_softc*) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RF_ACTIVE ; 
 int RF_ALLOCATED ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipc_release_region (struct chipc_softc*,struct chipc_region*,int) ; 

int
chipc_retain_region(struct chipc_softc *sc, struct chipc_region *cr, int flags)
{
	int error;

	KASSERT(!(flags &~ (RF_ACTIVE|RF_ALLOCATED)), ("unsupported flags"));

	CHIPC_LOCK(sc);

	/* Handle allocation */
	if (flags & RF_ALLOCATED) {
		/* If this is the first reference, allocate the resource */
		if (cr->cr_refs == 0) {
			KASSERT(cr->cr_res == NULL,
			    ("non-NULL resource has refcount"));

			/* Fetch initial resource ID */			
			if ((cr->cr_res_rid = cr->cr_rid) == -1) {
				CHIPC_UNLOCK(sc);
				return (EINVAL);
			}

			/* Allocate resource */
			cr->cr_res = bhnd_alloc_resource(sc->dev,
			    SYS_RES_MEMORY, &cr->cr_res_rid, cr->cr_addr,
			    cr->cr_end, cr->cr_count, RF_SHAREABLE);
			if (cr->cr_res == NULL) {
				CHIPC_UNLOCK(sc);
				return (ENXIO);
			}
		}
		
		/* Increment allocation refcount */
		cr->cr_refs++;
	}


	/* Handle activation */
	if (flags & RF_ACTIVE) {
		KASSERT(cr->cr_refs > 0,
		    ("cannot activate unallocated resource"));

		/* If this is the first reference, activate the resource */
		if (cr->cr_act_refs == 0) {
			error = bhnd_activate_resource(sc->dev, SYS_RES_MEMORY,
			    cr->cr_res_rid, cr->cr_res);
			if (error) {
				/* Drop any allocation reference acquired
				 * above */
				CHIPC_UNLOCK(sc);
				chipc_release_region(sc, cr,
				    flags &~ RF_ACTIVE);
				return (error);
			}
		}

		/* Increment activation refcount */
		cr->cr_act_refs++;
	}

	CHIPC_UNLOCK(sc);
	return (0);
}
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
struct chipc_region {int cr_act_refs; int cr_refs; int /*<<< orphan*/ * cr_res; int /*<<< orphan*/  cr_res_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPC_LOCK (struct chipc_softc*) ; 
 int /*<<< orphan*/  CHIPC_UNLOCK (struct chipc_softc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RF_ACTIVE ; 
 int RF_ALLOCATED ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_deactivate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
chipc_release_region(struct chipc_softc *sc, struct chipc_region *cr,
    int flags)
{
	int	error;

	CHIPC_LOCK(sc);
	error = 0;

	KASSERT(cr->cr_res != NULL, ("release on NULL region resource"));

	if (flags & RF_ACTIVE) {
		KASSERT(cr->cr_act_refs > 0, ("RF_ACTIVE over-released"));
		KASSERT(cr->cr_act_refs <= cr->cr_refs,
		     ("RF_ALLOCATED released with RF_ACTIVE held"));

		/* If this is the last reference, deactivate the resource */
		if (cr->cr_act_refs == 1) {
			error = bhnd_deactivate_resource(sc->dev,
			    SYS_RES_MEMORY, cr->cr_res_rid, cr->cr_res);
			if (error)
				goto done;
		}

		/* Drop our activation refcount */
		cr->cr_act_refs--;
	}

	if (flags & RF_ALLOCATED) {
		KASSERT(cr->cr_refs > 0, ("overrelease of refs"));
		/* If this is the last reference, release the resource */
		if (cr->cr_refs == 1) {
			error = bhnd_release_resource(sc->dev, SYS_RES_MEMORY,
			    cr->cr_res_rid, cr->cr_res);
			if (error)
				goto done;

			cr->cr_res = NULL;
		}

		/* Drop our allocation refcount */
		cr->cr_refs--;
	}

done:
	CHIPC_UNLOCK(sc);
	return (error);
}
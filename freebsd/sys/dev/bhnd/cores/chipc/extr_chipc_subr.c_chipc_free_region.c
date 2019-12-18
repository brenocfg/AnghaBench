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
struct chipc_region {scalar_t__ cr_refs; int /*<<< orphan*/ * cr_res; int /*<<< orphan*/  cr_res_rid; int /*<<< orphan*/  cr_region_num; int /*<<< orphan*/  cr_port_num; int /*<<< orphan*/  cr_port_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bhnd_port_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct chipc_region*,int /*<<< orphan*/ ) ; 

void
chipc_free_region(struct chipc_softc *sc, struct chipc_region *cr)
{
	KASSERT(cr->cr_refs == 0,
	    ("chipc %s%u.%u region has %u active references",
	     bhnd_port_type_name(cr->cr_port_type), cr->cr_port_num,
	     cr->cr_region_num, cr->cr_refs));

	if (cr->cr_res != NULL) {
		bhnd_release_resource(sc->dev, SYS_RES_MEMORY, cr->cr_res_rid,
		    cr->cr_res);
	}

	free(cr, M_BHND);
}
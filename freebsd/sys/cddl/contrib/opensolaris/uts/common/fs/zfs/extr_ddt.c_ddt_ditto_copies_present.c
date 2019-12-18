#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ddp_dva; } ;
typedef  TYPE_1__ ddt_phys_t ;
struct TYPE_5__ {TYPE_1__* dde_phys; } ;
typedef  TYPE_2__ ddt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t DDT_PHYS_DITTO ; 
 int DVA_GET_GANG (int /*<<< orphan*/ *) ; 
 scalar_t__ DVA_IS_VALID (int /*<<< orphan*/ *) ; 
 int SPA_DVAS_PER_BP ; 

int
ddt_ditto_copies_present(ddt_entry_t *dde)
{
	ddt_phys_t *ddp = &dde->dde_phys[DDT_PHYS_DITTO];
	dva_t *dva = ddp->ddp_dva;
	int copies = 0 - DVA_GET_GANG(dva);

	for (int d = 0; d < SPA_DVAS_PER_BP; d++, dva++)
		if (DVA_IS_VALID(dva))
			copies++;

	ASSERT(copies >= 0 && copies < SPA_DVAS_PER_BP);

	return (copies);
}
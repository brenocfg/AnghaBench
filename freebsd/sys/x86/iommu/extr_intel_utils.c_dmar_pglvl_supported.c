#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dmar_unit {int /*<<< orphan*/  hw_cap; } ;
struct TYPE_3__ {int pglvl; int cap; } ;

/* Variables and functions */
 int DMAR_CAP_SAGAW (int /*<<< orphan*/ ) ; 
 int nitems (TYPE_1__*) ; 
 TYPE_1__* sagaw_bits ; 

bool
dmar_pglvl_supported(struct dmar_unit *unit, int pglvl)
{
	int i;

	for (i = 0; i < nitems(sagaw_bits); i++) {
		if (sagaw_bits[i].pglvl != pglvl)
			continue;
		if ((DMAR_CAP_SAGAW(unit->hw_cap) & sagaw_bits[i].cap) != 0)
			return (true);
	}
	return (false);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tag; } ;
struct TYPE_4__ {scalar_t__ plan; } ;
struct uni_sap {TYPE_1__ selector; TYPE_2__ addr; int /*<<< orphan*/  bhli; int /*<<< orphan*/  blli_id3; int /*<<< orphan*/  blli_id2; } ;

/* Variables and functions */
 scalar_t__ UNISVE_ABSENT ; 
 int UNISVE_ERROR_ADDR_SEL_CONFLICT ; 
 scalar_t__ UNISVE_PRESENT ; 
 scalar_t__ UNI_ADDR_ATME ; 
 scalar_t__ UNI_ADDR_E164 ; 
 int unisve_check_addr (TYPE_2__*) ; 
 int unisve_check_bhli (int /*<<< orphan*/ *) ; 
 int unisve_check_blli_id2 (int /*<<< orphan*/ *) ; 
 int unisve_check_blli_id3 (int /*<<< orphan*/ *) ; 
 int unisve_check_selector (TYPE_1__*) ; 

int
unisve_check_sap(const struct uni_sap *sap)
{
	int err;

	if ((err = unisve_check_addr(&sap->addr)) != 0 ||
	    (err = unisve_check_selector(&sap->selector)) != 0 ||
	    (err = unisve_check_blli_id2(&sap->blli_id2)) != 0 ||
	    (err = unisve_check_blli_id3(&sap->blli_id3)) != 0 ||
	    (err = unisve_check_bhli(&sap->bhli)) != 0)
		return (err);

	if (sap->addr.plan == UNI_ADDR_E164) {
		if (sap->selector.tag == UNISVE_PRESENT)
			return (UNISVE_ERROR_ADDR_SEL_CONFLICT);
	} else if (sap->addr.plan == UNI_ADDR_ATME) {
		if (sap->selector.tag == UNISVE_ABSENT)
			return (UNISVE_ERROR_ADDR_SEL_CONFLICT);
	}
	return (0);
}
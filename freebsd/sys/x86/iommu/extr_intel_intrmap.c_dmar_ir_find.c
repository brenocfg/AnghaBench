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
typedef  int /*<<< orphan*/  uint16_t ;
struct dmar_unit {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ devclass_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  bootverbose ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 struct dmar_unit* dmar_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dmar_unit* dmar_find_hpet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmar_get_requester (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dmar_unit *
dmar_ir_find(device_t src, uint16_t *rid, int *is_dmar)
{
	devclass_t src_class;
	struct dmar_unit *unit;

	/*
	 * We need to determine if the interrupt source generates FSB
	 * interrupts.  If yes, it is either DMAR, in which case
	 * interrupts are not remapped.  Or it is HPET, and interrupts
	 * are remapped.  For HPET, source id is reported by HPET
	 * record in DMAR ACPI table.
	 */
	if (is_dmar != NULL)
		*is_dmar = FALSE;
	src_class = device_get_devclass(src);
	if (src_class == devclass_find("dmar")) {
		unit = NULL;
		if (is_dmar != NULL)
			*is_dmar = TRUE;
	} else if (src_class == devclass_find("hpet")) {
		unit = dmar_find_hpet(src, rid);
	} else {
		unit = dmar_find(src, bootverbose);
		if (unit != NULL && rid != NULL)
			dmar_get_requester(src, rid);
	}
	return (unit);
}
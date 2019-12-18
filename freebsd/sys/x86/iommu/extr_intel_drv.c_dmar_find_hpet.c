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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DMAR_SCOPE_TYPE_HPET ; 
 struct dmar_unit* dmar_find_nonpci (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpet_get_uid (int /*<<< orphan*/ ) ; 

struct dmar_unit *
dmar_find_hpet(device_t dev, uint16_t *rid)
{

	return (dmar_find_nonpci(hpet_get_uid(dev), ACPI_DMAR_SCOPE_TYPE_HPET,
	    rid));
}
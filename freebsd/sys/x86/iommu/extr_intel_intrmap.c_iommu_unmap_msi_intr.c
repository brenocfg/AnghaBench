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
typedef  int u_int ;
struct dmar_unit {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct dmar_unit* dmar_ir_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmar_ir_free_irte (struct dmar_unit*,int) ; 

int
iommu_unmap_msi_intr(device_t src, u_int cookie)
{
	struct dmar_unit *unit;

	if (cookie == -1)
		return (0);
	unit = dmar_ir_find(src, NULL, NULL);
	return (dmar_ir_free_irte(unit, cookie));
}
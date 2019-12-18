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
struct octeon_core_chip_data {scalar_t__ desired_en; scalar_t__ current_en; int /*<<< orphan*/  core_irq_mutex; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct octeon_core_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  octeon_irq_core_set_enable_local ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct irq_data*,int) ; 

__attribute__((used)) static void octeon_irq_core_bus_sync_unlock(struct irq_data *data)
{
	struct octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);

	if (cd->desired_en != cd->current_en) {
		on_each_cpu(octeon_irq_core_set_enable_local, data, 1);

		cd->current_en = cd->desired_en;
	}

	mutex_unlock(&cd->core_irq_mutex);
}
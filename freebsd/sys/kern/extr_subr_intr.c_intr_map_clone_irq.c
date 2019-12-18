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
typedef  int /*<<< orphan*/  u_int ;
struct intr_map_data {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  intr_map_copy_map_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,intptr_t*,struct intr_map_data**) ; 
 int /*<<< orphan*/  intr_map_irq (int /*<<< orphan*/ ,intptr_t,struct intr_map_data*) ; 

u_int
intr_map_clone_irq(u_int old_res_id)
{
	device_t map_dev;
	intptr_t map_xref;
	struct intr_map_data *data;

	intr_map_copy_map_data(old_res_id, &map_dev, &map_xref, &data);
	return (intr_map_irq(map_dev, map_xref, data));
}
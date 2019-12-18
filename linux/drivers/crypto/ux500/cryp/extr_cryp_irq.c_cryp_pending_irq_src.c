#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cryp_device_data {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  mis; } ;

/* Variables and functions */
 int readl_relaxed (int /*<<< orphan*/ *) ; 

bool cryp_pending_irq_src(struct cryp_device_data *device_data, u32 irq_src)
{
	return (readl_relaxed(&device_data->base->mis) & irq_src) > 0;
}
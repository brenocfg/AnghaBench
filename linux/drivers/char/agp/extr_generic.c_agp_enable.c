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
typedef  int /*<<< orphan*/  u32 ;
struct agp_bridge_data {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* agp_enable ) (struct agp_bridge_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct agp_bridge_data*,int /*<<< orphan*/ ) ; 

void agp_enable(struct agp_bridge_data *bridge, u32 mode)
{
	if (!bridge)
		return;
	bridge->driver->agp_enable(bridge, mode);
}
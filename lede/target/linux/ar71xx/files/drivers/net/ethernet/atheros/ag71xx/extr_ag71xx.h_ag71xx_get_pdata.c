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
struct ag71xx_platform_data {int dummy; } ;
struct ag71xx {TYPE_2__* pdev; } ;
struct TYPE_3__ {struct ag71xx_platform_data* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ag71xx_platform_data *ag71xx_get_pdata(struct ag71xx *ag)
{
	return ag->pdev->dev.platform_data;
}
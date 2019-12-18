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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_GPIO_CONDITION_MET_EV ; 
 int /*<<< orphan*/  dln2_unregister_event_cb (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_gpio_remove(struct platform_device *pdev)
{
	dln2_unregister_event_cb(pdev, DLN2_GPIO_CONDITION_MET_EV);

	return 0;
}
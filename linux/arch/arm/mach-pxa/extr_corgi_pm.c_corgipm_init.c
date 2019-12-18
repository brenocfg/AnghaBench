#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int batfull_irq; } ;
struct TYPE_7__ {TYPE_6__* platform_data; } ;
struct TYPE_8__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 TYPE_6__ corgi_pm_machinfo ; 
 TYPE_2__* corgipm_device ; 
 int /*<<< orphan*/  machine_is_corgi () ; 
 int /*<<< orphan*/  machine_is_husky () ; 
 int /*<<< orphan*/  machine_is_shepherd () ; 
 int platform_device_add (TYPE_2__*) ; 
 TYPE_2__* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_2__*) ; 

__attribute__((used)) static int corgipm_init(void)
{
	int ret;

	if (!machine_is_corgi() && !machine_is_shepherd()
			&& !machine_is_husky())
		return -ENODEV;

	corgipm_device = platform_device_alloc("sharpsl-pm", -1);
	if (!corgipm_device)
		return -ENOMEM;

	if (!machine_is_corgi())
	    corgi_pm_machinfo.batfull_irq = 1;

	corgipm_device->dev.platform_data = &corgi_pm_machinfo;
	ret = platform_device_add(corgipm_device);

	if (ret)
		platform_device_put(corgipm_device);

	return ret;
}
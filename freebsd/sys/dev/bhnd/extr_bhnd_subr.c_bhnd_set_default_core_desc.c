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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_get_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_set_custom_core_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bhnd_set_default_core_desc(device_t dev)
{
	bhnd_set_custom_core_desc(dev, bhnd_get_device_name(dev));
}
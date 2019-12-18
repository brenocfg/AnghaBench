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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RANDOM_TRUST_BOOTLOADER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_device_randomness (void const*,unsigned int) ; 
 int /*<<< orphan*/  add_hwgenerator_randomness (void const*,unsigned int,unsigned int) ; 

void add_bootloader_randomness(const void *buf, unsigned int size)
{
	if (IS_ENABLED(CONFIG_RANDOM_TRUST_BOOTLOADER))
		add_hwgenerator_randomness(buf, size, size * 8);
	else
		add_device_randomness(buf, size);
}
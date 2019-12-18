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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 scalar_t__ scx200_gpio_base ; 
 int /*<<< orphan*/  scx200_gpio_config_lock ; 

u32 scx200_gpio_configure(unsigned index, u32 mask, u32 bits)
{
	u32 config, new_config;

	mutex_lock(&scx200_gpio_config_lock);

	outl(index, scx200_gpio_base + 0x20);
	config = inl(scx200_gpio_base + 0x24);

	new_config = (config & mask) | bits;
	outl(new_config, scx200_gpio_base + 0x24);

	mutex_unlock(&scx200_gpio_config_lock);

	return config;
}
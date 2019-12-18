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
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ NVRAM_BYTES ; 
 int /*<<< orphan*/  __nvram_set_checksum () ; 
 int /*<<< orphan*/  __nvram_write_byte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

long atari_nvram_initialize(void)
{
	loff_t i;

	spin_lock_irq(&rtc_lock);
	for (i = 0; i < NVRAM_BYTES; ++i)
		__nvram_write_byte(0, i);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);
	return 0;
}
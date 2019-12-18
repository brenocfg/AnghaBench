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
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ NVRAM_BYTES ; 
 int /*<<< orphan*/  __nvram_check_checksum () ; 
 int /*<<< orphan*/  __nvram_set_checksum () ; 
 int /*<<< orphan*/  __nvram_write_byte (char,scalar_t__) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

ssize_t atari_nvram_write(char *buf, size_t count, loff_t *ppos)
{
	char *p = buf;
	loff_t i;

	spin_lock_irq(&rtc_lock);
	if (!__nvram_check_checksum()) {
		spin_unlock_irq(&rtc_lock);
		return -EIO;
	}
	for (i = *ppos; count > 0 && i < NVRAM_BYTES; --count, ++i, ++p)
		__nvram_write_byte(*p, i);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);

	*ppos = i;
	return p - buf;
}
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
 int /*<<< orphan*/  __raw_writeb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  lock_cmos_prefix (unsigned char) ; 
 int /*<<< orphan*/  lock_cmos_suffix (unsigned char) ; 
 scalar_t__ vrtc_virt_base ; 

void vrtc_cmos_write(unsigned char val, unsigned char reg)
{
	if (reg > 0xd || !vrtc_virt_base)
		return;

	lock_cmos_prefix(reg);
	__raw_writeb(val, vrtc_virt_base + (reg << 2));
	lock_cmos_suffix(reg);
}
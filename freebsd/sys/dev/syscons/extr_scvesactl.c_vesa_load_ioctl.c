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
 int EBUSY ; 
 scalar_t__ prev_user_ioctl ; 
 scalar_t__ sc_user_ioctl ; 
 scalar_t__ vesa_ioctl ; 

int
vesa_load_ioctl(void)
{
	if (prev_user_ioctl)
		return EBUSY;
	prev_user_ioctl = sc_user_ioctl;
	sc_user_ioctl = vesa_ioctl;
	return 0;
}
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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ gpio ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (scalar_t__,int) ; 

__attribute__((used)) static void
led_func(void *ptr, int onoff)
{
	uint32_t u;
	int bit;

	bit = *(int *)ptr;
	if (bit < 0) {
		bit = -bit;
		onoff = !onoff;
	}

	u = inl(gpio + 4);
	if (onoff)
		u |= 1 << bit;
	else
		u &= ~(1 << bit);
	outl(gpio, u);
}
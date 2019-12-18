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
 int* emu10k1_adcspeed ; 

__attribute__((used)) static int
emu_k1_recval(int speed)
{
	int val;

	val = 0;
	while ((val < 7) && (speed < emu10k1_adcspeed[val]))
		val++;
	return (val);
}
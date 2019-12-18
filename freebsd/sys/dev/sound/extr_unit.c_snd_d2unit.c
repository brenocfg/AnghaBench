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
 int MKMASK (int) ; 
 int /*<<< orphan*/  SND_UNIT_ASSERT () ; 
 int snd_c_shift ; 

int
snd_d2unit(int d)
{
	SND_UNIT_ASSERT();

	return ((d & MKMASK(d)) << snd_c_shift);
}
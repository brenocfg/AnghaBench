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
 scalar_t__* facility ; 
 scalar_t__* facility_initialized ; 

void
p31b_unsetcfg(int num)
{

	facility[num - 1] = 0;
	facility_initialized[num - 1] = 0;
}
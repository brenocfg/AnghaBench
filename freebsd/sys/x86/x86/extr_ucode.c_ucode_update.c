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
 scalar_t__ atomic_swap_ptr (void*,uintptr_t) ; 
 void* early_ucode_data ; 
 int /*<<< orphan*/  ucode_data ; 

void *
ucode_update(void *newdata)
{

	newdata = (void *)atomic_swap_ptr((void *)&ucode_data,
	    (uintptr_t)newdata);
	if (newdata == early_ucode_data)
		newdata = NULL;
	return (newdata);
}
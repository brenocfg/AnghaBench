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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static bool _fs_match_exact_val(void *mask, void *val1, void *val2, size_t size)
{
	unsigned int i;

	/* TODO: optimize by comparing 64bits when possible */
	for (i = 0; i < size; i++, mask++, val1++, val2++)
		if ((*((u8 *)val1) & (*(u8 *)mask)) !=
		    ((*(u8 *)val2) & (*(u8 *)mask)))
			return false;

	return true;
}
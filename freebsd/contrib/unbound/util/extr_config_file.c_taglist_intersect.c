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
typedef  int uint8_t ;

/* Variables and functions */

int taglist_intersect(uint8_t* list1, size_t list1len, uint8_t* list2,
	size_t list2len)
{
	size_t i;
	if(!list1 || !list2)
		return 0;
	for(i=0; i<list1len && i<list2len; i++) {
		if((list1[i] & list2[i]) != 0)
			return 1;
	}
	return 0;
}
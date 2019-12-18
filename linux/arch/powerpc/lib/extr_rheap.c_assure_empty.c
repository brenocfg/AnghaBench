#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int empty_slots; int max_blocks; } ;
typedef  TYPE_1__ rh_info_t ;

/* Variables and functions */
 int EINVAL ; 
 int grow (TYPE_1__*,int) ; 

__attribute__((used)) static int assure_empty(rh_info_t * info, int slots)
{
	int max_blocks;

	/* This function is not meant to be used to grow uncontrollably */
	if (slots >= 4)
		return -EINVAL;

	/* Enough space */
	if (info->empty_slots >= slots)
		return 0;

	/* Next 16 sized block */
	max_blocks = ((info->max_blocks + slots) + 15) & ~15;

	return grow(info, max_blocks);
}
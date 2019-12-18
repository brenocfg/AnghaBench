#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ format_id; } ;

/* Variables and functions */
 int GIT_HASH_NALGOS ; 
 int GIT_HASH_UNKNOWN ; 
 TYPE_1__* hash_algos ; 

int hash_algo_by_id(uint32_t format_id)
{
	int i;
	for (i = 1; i < GIT_HASH_NALGOS; i++)
		if (format_id == hash_algos[i].format_id)
			return i;
	return GIT_HASH_UNKNOWN;
}
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
struct pt_tnt_cache {int index; int tnt; } ;

/* Variables and functions */
 int pte_bad_query ; 
 int pte_invalid ; 

int pt_tnt_cache_query(struct pt_tnt_cache *cache)
{
	int taken;

	if (!cache)
		return -pte_invalid;

	if (!cache->index)
		return -pte_bad_query;

	taken = (cache->tnt & cache->index) != 0;
	cache->index >>= 1;

	return taken;
}
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
struct pt_tnt_cache {scalar_t__ index; } ;

/* Variables and functions */
 int pte_invalid ; 

int pt_tnt_cache_is_empty(const struct pt_tnt_cache *cache)
{
	if (!cache)
		return -pte_invalid;

	return cache->index == 0;
}
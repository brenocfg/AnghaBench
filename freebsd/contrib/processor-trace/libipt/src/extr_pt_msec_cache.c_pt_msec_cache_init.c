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
struct pt_msec_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_msec_cache*,int /*<<< orphan*/ ,int) ; 
 int pte_internal ; 

int pt_msec_cache_init(struct pt_msec_cache *cache)
{
	if (!cache)
		return -pte_internal;

	memset(cache, 0, sizeof(*cache));

	return 0;
}
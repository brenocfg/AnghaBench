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
struct ttm_mem_zone {char* name; scalar_t__ used_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_ZONE ; 
 int /*<<< orphan*/  free (struct ttm_mem_zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long long) ; 

__attribute__((used)) static void ttm_mem_zone_kobj_release(struct ttm_mem_zone *zone)
{

	printf("[TTM] Zone %7s: Used memory at exit: %llu kiB\n",
		zone->name, (unsigned long long)zone->used_mem >> 10);
	free(zone, M_TTM_ZONE);
}
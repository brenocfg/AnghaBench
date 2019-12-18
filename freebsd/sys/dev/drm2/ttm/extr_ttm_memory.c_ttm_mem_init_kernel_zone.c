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
typedef  int uint64_t ;
struct ttm_mem_zone {char* name; int zone_mem; int max_mem; int emer_mem; int swap_limit; int /*<<< orphan*/  kobj_ref; struct ttm_mem_global* glob; scalar_t__ used_mem; } ;
struct ttm_mem_global {int /*<<< orphan*/  num_zones; struct ttm_mem_zone** zones; struct ttm_mem_zone* zone_kernel; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_ZONE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct ttm_mem_zone* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ttm_mem_init_kernel_zone(struct ttm_mem_global *glob,
    uint64_t mem)
{
	struct ttm_mem_zone *zone;

	zone = malloc(sizeof(*zone), M_TTM_ZONE, M_WAITOK | M_ZERO);

	zone->name = "kernel";
	zone->zone_mem = mem;
	zone->max_mem = mem >> 1;
	zone->emer_mem = (mem >> 1) + (mem >> 2);
	zone->swap_limit = zone->max_mem - (mem >> 3);
	zone->used_mem = 0;
	zone->glob = glob;
	glob->zone_kernel = zone;
	refcount_init(&zone->kobj_ref, 1);
	glob->zones[glob->num_zones++] = zone;
	return 0;
}
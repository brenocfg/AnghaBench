#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_slab_t ;
typedef  TYPE_3__* uma_keg_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  uk_pgoff; int /*<<< orphan*/  uk_hash; } ;
struct TYPE_12__ {TYPE_3__* us_keg; } ;
struct TYPE_11__ {int uz_flags; TYPE_3__* uz_keg; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEG_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  KEG_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 uintptr_t UMA_SLAB_MASK ; 
 int UMA_ZONE_HASH ; 
 int UMA_ZONE_VTOSLAB ; 
 TYPE_2__* hash_sfind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slab_free_item (TYPE_1__*,TYPE_2__*,void*) ; 
 TYPE_2__* vtoslab (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zone_release(uma_zone_t zone, void **bucket, int cnt)
{
	void *item;
	uma_slab_t slab;
	uma_keg_t keg;
	uint8_t *mem;
	int i;

	keg = zone->uz_keg;
	KEG_LOCK(keg);
	for (i = 0; i < cnt; i++) {
		item = bucket[i];
		if (!(zone->uz_flags & UMA_ZONE_VTOSLAB)) {
			mem = (uint8_t *)((uintptr_t)item & (~UMA_SLAB_MASK));
			if (zone->uz_flags & UMA_ZONE_HASH) {
				slab = hash_sfind(&keg->uk_hash, mem);
			} else {
				mem += keg->uk_pgoff;
				slab = (uma_slab_t)mem;
			}
		} else {
			slab = vtoslab((vm_offset_t)item);
			MPASS(slab->us_keg == keg);
		}
		slab_free_item(zone, slab, item);
	}
	KEG_UNLOCK(keg);
}
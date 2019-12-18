#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ck_ht_map {unsigned long step; size_t mask; } ;
struct TYPE_3__ {unsigned long value; } ;
typedef  TYPE_1__ ck_ht_hash_t ;

/* Variables and functions */
 size_t CK_HT_BUCKET_LENGTH ; 
 int CK_HT_BUCKET_MASK ; 
 unsigned long CK_HT_BUCKET_SHIFT ; 

__attribute__((used)) static inline size_t
ck_ht_map_probe_next(struct ck_ht_map *map, size_t offset, ck_ht_hash_t h, size_t probes)
{
	ck_ht_hash_t r;
	size_t stride;
	unsigned long level = (unsigned long)probes >> CK_HT_BUCKET_SHIFT;

	r.value = (h.value >> map->step) >> level;
	stride = (r.value & ~CK_HT_BUCKET_MASK) << 1
		     | (r.value & CK_HT_BUCKET_MASK);

	return (offset + level +
	    (stride | CK_HT_BUCKET_LENGTH)) & map->mask;
}
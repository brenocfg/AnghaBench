#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rrset_ref {int /*<<< orphan*/  id; TYPE_2__* key; } ;
struct rrset_cache {int dummy; } ;
struct regional {int dummy; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  hash; } ;
struct TYPE_4__ {TYPE_1__ entry; } ;

/* Variables and functions */
 size_t RR_COUNT_MAX ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 scalar_t__ regional_alloc (struct regional*,int) ; 
 int /*<<< orphan*/  rrset_cache_touch (struct rrset_cache*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
rrset_array_unlock_touch(struct rrset_cache* r, struct regional* scratch,
	struct rrset_ref* ref, size_t count)
{
	hashvalue_type* h;
	size_t i;
	if(count > RR_COUNT_MAX || !(h = (hashvalue_type*)regional_alloc(
		scratch, sizeof(hashvalue_type)*count))) {
		log_warn("rrset LRU: memory allocation failed");
		h = NULL;
	} else 	/* store hash values */
		for(i=0; i<count; i++)
			h[i] = ref[i].key->entry.hash;
	/* unlock */
	for(i=0; i<count; i++) {
		if(i>0 && ref[i].key == ref[i-1].key)
			continue; /* only unlock items once */
		lock_rw_unlock(&ref[i].key->entry.lock);
	}
	if(h) {
		/* LRU touch, with no rrset locks held */
		for(i=0; i<count; i++) {
			if(i>0 && ref[i].key == ref[i-1].key)
				continue; /* only touch items once */
			rrset_cache_touch(r, ref[i].key, h[i], ref[i].id);
		}
	}
}
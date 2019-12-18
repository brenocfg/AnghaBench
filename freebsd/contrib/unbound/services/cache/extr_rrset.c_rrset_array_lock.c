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
typedef  scalar_t__ time_t ;
struct rrset_ref {scalar_t__ id; TYPE_2__* key; } ;
struct packed_rrset_data {scalar_t__ ttl; } ;
struct TYPE_3__ {scalar_t__ data; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ id; TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrset_array_unlock (struct rrset_ref*,size_t) ; 

int 
rrset_array_lock(struct rrset_ref* ref, size_t count, time_t timenow)
{
	size_t i;
	for(i=0; i<count; i++) {
		if(i>0 && ref[i].key == ref[i-1].key)
			continue; /* only lock items once */
		lock_rw_rdlock(&ref[i].key->entry.lock);
		if(ref[i].id != ref[i].key->id || timenow >
			((struct packed_rrset_data*)(ref[i].key->entry.data))
			->ttl) {
			/* failure! rollback our readlocks */
			rrset_array_unlock(ref, i+1);
			return 0;
		}
	}
	return 1;
}
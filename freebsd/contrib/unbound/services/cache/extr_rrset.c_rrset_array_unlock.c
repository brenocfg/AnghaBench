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
struct rrset_ref {TYPE_2__* key; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 

void 
rrset_array_unlock(struct rrset_ref* ref, size_t count)
{
	size_t i;
	for(i=0; i<count; i++) {
		if(i>0 && ref[i].key == ref[i-1].key)
			continue; /* only unlock items once */
		lock_rw_unlock(&ref[i].key->entry.lock);
	}
}
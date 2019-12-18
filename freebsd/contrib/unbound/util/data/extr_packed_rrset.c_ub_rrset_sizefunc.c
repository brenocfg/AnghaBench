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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int dname_len; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; TYPE_1__ rk; } ;
struct packed_rrset_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ lock_get_mem (int /*<<< orphan*/ *) ; 
 scalar_t__ packed_rrset_sizeof (struct packed_rrset_data*) ; 

size_t 
ub_rrset_sizefunc(void* key, void* data)
{
	struct ub_packed_rrset_key* k = (struct ub_packed_rrset_key*)key;
	struct packed_rrset_data* d = (struct packed_rrset_data*)data;
	size_t s = sizeof(struct ub_packed_rrset_key) + k->rk.dname_len;
	s += packed_rrset_sizeof(d) + lock_get_mem(&k->entry.lock);
	return s;
}
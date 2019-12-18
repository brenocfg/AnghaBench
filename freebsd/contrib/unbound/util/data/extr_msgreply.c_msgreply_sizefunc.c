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
struct ub_packed_rrset_key {int dummy; } ;
struct rrset_ref {int dummy; } ;
struct reply_info {int rrset_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int qname_len; } ;
struct msgreply_entry {TYPE_2__ entry; TYPE_1__ key; } ;

/* Variables and functions */
 int lock_get_mem (int /*<<< orphan*/ *) ; 

size_t 
msgreply_sizefunc(void* k, void* d)
{
	struct msgreply_entry* q = (struct msgreply_entry*)k;
	struct reply_info* r = (struct reply_info*)d;
	size_t s = sizeof(struct msgreply_entry) + sizeof(struct reply_info)
		+ q->key.qname_len + lock_get_mem(&q->entry.lock)
		- sizeof(struct rrset_ref);
	s += r->rrset_count * sizeof(struct rrset_ref);
	s += r->rrset_count * sizeof(struct ub_packed_rrset_key*);
	return s;
}
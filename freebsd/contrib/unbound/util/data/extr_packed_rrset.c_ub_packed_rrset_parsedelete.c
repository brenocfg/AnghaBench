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
struct TYPE_4__ {int /*<<< orphan*/ * dname; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
struct ub_packed_rrset_key {scalar_t__ id; TYPE_2__ rk; TYPE_1__ entry; } ;
struct alloc_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_special_release (struct alloc_cache*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
ub_packed_rrset_parsedelete(struct ub_packed_rrset_key* pkey,
        struct alloc_cache* alloc)
{
	if(!pkey)
		return;
	free(pkey->entry.data);
	pkey->entry.data = NULL;
	free(pkey->rk.dname);
	pkey->rk.dname = NULL;
	pkey->id = 0;
	alloc_special_release(alloc, pkey);
}
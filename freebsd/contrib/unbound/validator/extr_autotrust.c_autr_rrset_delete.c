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
struct TYPE_4__ {struct ub_packed_rrset_key* data; } ;
struct TYPE_3__ {struct ub_packed_rrset_key* dname; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; TYPE_1__ rk; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ub_packed_rrset_key*) ; 

__attribute__((used)) static void
autr_rrset_delete(struct ub_packed_rrset_key* r)
{
	if(r) {
		free(r->rk.dname);
		free(r->entry.data);
		free(r);
	}
}
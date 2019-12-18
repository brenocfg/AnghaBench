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
struct TYPE_4__ {struct ub_packed_rrset_key* dname; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; struct ub_packed_rrset_key* rr_len; struct ub_packed_rrset_key* rr_ttl; struct ub_packed_rrset_key* rr_data; TYPE_1__ entry; } ;
struct packed_rrset_data {TYPE_2__ rk; struct packed_rrset_data* rr_len; struct packed_rrset_data* rr_ttl; struct packed_rrset_data* rr_data; TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ub_packed_rrset_key*) ; 

__attribute__((used)) static void
assembled_rrset_delete(struct ub_packed_rrset_key* pkey)
{
	if(!pkey) return;
	if(pkey->entry.data) {
		struct packed_rrset_data* pd = (struct packed_rrset_data*)
			pkey->entry.data;
		free(pd->rr_data);
		free(pd->rr_ttl);
		free(pd->rr_len);
		free(pd);
	}
	free(pkey->rk.dname);
	free(pkey);
}
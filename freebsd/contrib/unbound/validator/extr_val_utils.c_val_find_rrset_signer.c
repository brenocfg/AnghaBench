#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {scalar_t__ rrsig_count; size_t count; int /*<<< orphan*/ * rr_len; int /*<<< orphan*/ * rr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  rrsig_get_signer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 

void 
val_find_rrset_signer(struct ub_packed_rrset_key* rrset, uint8_t** sname,
	size_t* slen)
{
	struct packed_rrset_data* d = (struct packed_rrset_data*)
		rrset->entry.data;
	/* return signer for first signature, or NULL */
	if(d->rrsig_count == 0) {
		*sname = NULL;
		*slen = 0;
		return;
	}
	/* get rrsig signer name out of the signature */
	rrsig_get_signer(d->rr_data[d->count], d->rr_len[d->count], 
		sname, slen);
}
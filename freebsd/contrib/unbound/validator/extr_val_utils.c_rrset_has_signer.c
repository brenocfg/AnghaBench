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
struct packed_rrset_data {size_t count; size_t rrsig_count; int* rr_len; scalar_t__* rr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_valid (scalar_t__,int) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
rrset_has_signer(struct ub_packed_rrset_key* rrset, uint8_t* name, size_t len)
{
	struct packed_rrset_data* d = (struct packed_rrset_data*)rrset->
		entry.data;
	size_t i;
	for(i = d->count; i< d->count+d->rrsig_count; i++) {
		if(d->rr_len[i] > 2+18+len) {
			/* at least rdatalen + signature + signame (+1 sig)*/
			if(!dname_valid(d->rr_data[i]+2+18, d->rr_len[i]-2-18))
				continue;
			if(query_dname_compare(name, d->rr_data[i]+2+18) == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}
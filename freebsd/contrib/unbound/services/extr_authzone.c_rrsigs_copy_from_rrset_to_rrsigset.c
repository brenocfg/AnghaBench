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
typedef  int /*<<< orphan*/  time_t ;
struct auth_rrset {TYPE_1__* data; } ;
struct TYPE_2__ {size_t rrsig_count; size_t count; size_t* rr_len; int /*<<< orphan*/ * rr_ttl; int /*<<< orphan*/ ** rr_data; } ;

/* Variables and functions */
 scalar_t__ rdata_duplicate (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rrset_add_rr (struct auth_rrset*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rrsigs_copy_from_rrset_to_rrsigset(struct auth_rrset* rrset,
	struct auth_rrset* rrsigset)
{
	size_t i;
	if(rrset->data->rrsig_count == 0)
		return 1;

	/* move them over one by one, because there might be duplicates,
	 * duplicates are ignored */
	for(i=rrset->data->count;
		i<rrset->data->count+rrset->data->rrsig_count; i++) {
		uint8_t* rdata = rrset->data->rr_data[i];
		size_t rdatalen = rrset->data->rr_len[i];
		time_t rr_ttl  = rrset->data->rr_ttl[i];

		if(rdata_duplicate(rrsigset->data, rdata, rdatalen)) {
			continue;
		}
		if(!rrset_add_rr(rrsigset, rr_ttl, rdata, rdatalen, 0))
			return 0;
	}
	return 1;
}
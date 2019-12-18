#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct packed_rrset_data {size_t count; size_t rrsig_count; size_t* rr_len; int /*<<< orphan*/ ** rr_data; int /*<<< orphan*/ * rr_ttl; } ;

/* Variables and functions */

void 
packed_rrset_ptr_fixup(struct packed_rrset_data* data)
{
	size_t i;
	size_t total = data->count + data->rrsig_count;
	uint8_t* nextrdata;
	/* fixup pointers in packed rrset data */
	data->rr_len = (size_t*)((uint8_t*)data +
		sizeof(struct packed_rrset_data));
	data->rr_data = (uint8_t**)&(data->rr_len[total]);
	data->rr_ttl = (time_t*)&(data->rr_data[total]);
	nextrdata = (uint8_t*)&(data->rr_ttl[total]);
	for(i=0; i<total; i++) {
		data->rr_data[i] = nextrdata;
		nextrdata += data->rr_len[i];
	}
}
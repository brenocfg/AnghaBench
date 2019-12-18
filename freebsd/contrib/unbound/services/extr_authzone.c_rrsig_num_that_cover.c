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
typedef  scalar_t__ uint16_t ;
struct packed_rrset_data {size_t count; size_t rrsig_count; scalar_t__* rr_len; int /*<<< orphan*/ * rr_data; } ;
struct auth_rrset {scalar_t__ type; struct packed_rrset_data* data; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ rrsig_rdata_get_type_covered (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static size_t
rrsig_num_that_cover(struct auth_rrset* rrsig, uint16_t rr_type, size_t* sigsz)
{
	struct packed_rrset_data* d = rrsig->data;
	size_t i, num = 0;
	*sigsz = 0;
	log_assert(d && rrsig->type == LDNS_RR_TYPE_RRSIG);
	for(i=0; i<d->count+d->rrsig_count; i++) {
		if(rrsig_rdata_get_type_covered(d->rr_data[i],
			d->rr_len[i]) == rr_type) {
			num++;
			(*sigsz) += d->rr_len[i];
		}
	}
	return num;
}
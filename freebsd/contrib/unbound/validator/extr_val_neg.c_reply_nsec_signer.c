#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct reply_info {size_t an_numrrsets; size_t ns_numrrsets; TYPE_3__** rrsets; } ;
struct packed_rrset_data {scalar_t__ rrsig_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_2__ rk; TYPE_1__ entry; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_find_rrset_signer (TYPE_3__*,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static uint8_t* reply_nsec_signer(struct reply_info* rep, size_t* signer_len,
	uint16_t* dclass)
{
	size_t i;
	struct packed_rrset_data* d;
	uint8_t* s;
	for(i=rep->an_numrrsets; i< rep->an_numrrsets+rep->ns_numrrsets; i++){
		if(ntohs(rep->rrsets[i]->rk.type) == LDNS_RR_TYPE_NSEC ||
			ntohs(rep->rrsets[i]->rk.type) == LDNS_RR_TYPE_NSEC3) {
			d = (struct packed_rrset_data*)rep->rrsets[i]->
				entry.data;
			/* return first signer name of first NSEC */
			if(d->rrsig_count != 0) {
				val_find_rrset_signer(rep->rrsets[i],
					&s, signer_len);
				if(s && *signer_len) {
					*dclass = ntohs(rep->rrsets[i]->
						rk.rrset_class);
					return s;
				}
			}
		}
	}
	return 0;
}
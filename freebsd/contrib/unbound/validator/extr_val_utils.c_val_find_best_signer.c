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
struct query_info {int /*<<< orphan*/ * qname; } ;
struct packed_rrset_data {size_t count; size_t rrsig_count; int* rr_len; int /*<<< orphan*/ ** rr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
val_find_best_signer(struct ub_packed_rrset_key* rrset, 
	struct query_info* qinf, uint8_t** signer_name, size_t* signer_len, 
	int* matchcount)
{
	struct packed_rrset_data* d = (struct packed_rrset_data*)
		rrset->entry.data;
	uint8_t* sign;
	size_t i;
	int m;
	for(i=d->count; i<d->count+d->rrsig_count; i++) {
		sign = d->rr_data[i]+2+18;
		/* look at signatures that are valid (long enough),
		 * and have a signer name that is a superdomain of qname,
		 * and then check the number of labels in the shared topdomain
		 * improve the match if possible */
		if(d->rr_len[i] > 2+19 && /* rdata, sig + root label*/
			dname_subdomain_c(qinf->qname, sign)) {
			(void)dname_lab_cmp(qinf->qname, 
				dname_count_labels(qinf->qname), 
				sign, dname_count_labels(sign), &m);
			if(m > *matchcount) {
				*matchcount = m;
				*signer_name = sign;
				(void)dname_count_size_labels(*signer_name,
					signer_len);
			}
		}
	}
}
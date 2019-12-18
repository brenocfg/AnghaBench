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
typedef  int /*<<< orphan*/  uint8_t ;
struct val_neg_data {int dummy; } ;
struct reply_info {size_t an_numrrsets; size_t ns_numrrsets; TYPE_2__** rrsets; } ;
struct TYPE_3__ {size_t dname_len; int /*<<< orphan*/ * dname; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 int /*<<< orphan*/  dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t calc_data_need(struct reply_info* rep)
{
	uint8_t* d;
	size_t i, len, res = 0;

	for(i=rep->an_numrrsets; i<rep->an_numrrsets+rep->ns_numrrsets; i++) {
		if(ntohs(rep->rrsets[i]->rk.type) == LDNS_RR_TYPE_NSEC) {
			d = rep->rrsets[i]->rk.dname;
			len = rep->rrsets[i]->rk.dname_len;
			res = sizeof(struct val_neg_data) + len;
			while(!dname_is_root(d)) {
				log_assert(len > 1); /* not root label */
				dname_remove_label(&d, &len);
				res += sizeof(struct val_neg_data) + len;
			}
		}
	}
	return res;
}
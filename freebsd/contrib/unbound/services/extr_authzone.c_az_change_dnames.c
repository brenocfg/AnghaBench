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
struct dns_msg {TYPE_3__* rep; } ;
struct TYPE_6__ {size_t rrset_count; size_t an_numrrsets; TYPE_2__** rrsets; } ;
struct TYPE_4__ {size_t dname_len; int /*<<< orphan*/ * dname; } ;
struct TYPE_5__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
az_change_dnames(struct dns_msg* msg, uint8_t* oldname, uint8_t* newname,
	size_t newlen, int an_only)
{
	size_t i;
	size_t start = 0, end = msg->rep->rrset_count;
	if(!an_only) start = msg->rep->an_numrrsets;
	if(an_only) end = msg->rep->an_numrrsets;
	for(i=start; i<end; i++) {
		/* allocated in region so we can change the ptrs */
		if(query_dname_compare(msg->rep->rrsets[i]->rk.dname, oldname)
			== 0) {
			msg->rep->rrsets[i]->rk.dname = newname;
			msg->rep->rrsets[i]->rk.dname_len = newlen;
		}
	}
}
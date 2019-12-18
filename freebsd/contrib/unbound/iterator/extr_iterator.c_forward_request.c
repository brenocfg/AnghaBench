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
struct module_qstate {int /*<<< orphan*/  region; TYPE_1__* env; } ;
struct TYPE_5__ {size_t qname_len; scalar_t__ qtype; int /*<<< orphan*/  qclass; int /*<<< orphan*/ * qname; } ;
struct iter_qstate {TYPE_3__* dp; int /*<<< orphan*/  chase_flags; TYPE_2__ qchase; scalar_t__ refetch_glue; } ;
struct delegpt {int dummy; } ;
struct TYPE_6__ {size_t namelen; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RD ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 TYPE_3__* delegpt_copy (struct delegpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 struct delegpt* forwards_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
forward_request(struct module_qstate* qstate, struct iter_qstate* iq)
{
	struct delegpt* dp;
	uint8_t* delname = iq->qchase.qname;
	size_t delnamelen = iq->qchase.qname_len;
	if(iq->refetch_glue && iq->dp) {
		delname = iq->dp->name;
		delnamelen = iq->dp->namelen;
	}
	/* strip one label off of DS query to lookup higher for it */
	if( (iq->qchase.qtype == LDNS_RR_TYPE_DS || iq->refetch_glue)
		&& !dname_is_root(iq->qchase.qname))
		dname_remove_label(&delname, &delnamelen);
	dp = forwards_lookup(qstate->env->fwds, delname, iq->qchase.qclass);
	if(!dp) 
		return 0;
	/* send recursion desired to forward addr */
	iq->chase_flags |= BIT_RD; 
	iq->dp = delegpt_copy(dp, qstate->region);
	/* iq->dp checked by caller */
	verbose(VERB_ALGO, "forwarding request");
	return 1;
}
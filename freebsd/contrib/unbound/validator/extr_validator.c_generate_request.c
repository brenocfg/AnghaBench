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
typedef  scalar_t__ uint16_t ;
struct val_qstate {int /*<<< orphan*/  chain_blacklist; } ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * local_alias; scalar_t__ qclass; scalar_t__ qtype; int /*<<< orphan*/ * qname; } ;
struct module_qstate {int /*<<< orphan*/ * ext_state; int /*<<< orphan*/  region; int /*<<< orphan*/  blacklist; TYPE_1__* env; scalar_t__* minfo; } ;
struct mesh_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* attach_sub ) (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int,struct module_qstate**) ;int /*<<< orphan*/  (* add_sub ) (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int,struct module_qstate**,struct mesh_state**) ;scalar_t__ (* detect_cycle ) (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ BIT_RD ; 
 scalar_t__ LDNS_RR_TYPE_DLV ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_add_sub (int /*<<< orphan*/  (*) (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int,struct module_qstate**,struct mesh_state**)) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_attach_sub (int /*<<< orphan*/  (*) (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int,struct module_qstate**)) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_detect_cycle (scalar_t__ (*) (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int)) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,struct query_info*) ; 
 int /*<<< orphan*/  module_wait_subquery ; 
 int /*<<< orphan*/  sock_list_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int,struct module_qstate**,struct mesh_state**) ; 
 int /*<<< orphan*/  stub3 (struct module_qstate*,struct query_info*,scalar_t__,int /*<<< orphan*/ ,int,struct module_qstate**) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
generate_request(struct module_qstate* qstate, int id, uint8_t* name, 
	size_t namelen, uint16_t qtype, uint16_t qclass, uint16_t flags, 
	struct module_qstate** newq, int detached)
{
	struct val_qstate* vq = (struct val_qstate*)qstate->minfo[id];
	struct query_info ask;
	int valrec;
	ask.qname = name;
	ask.qname_len = namelen;
	ask.qtype = qtype;
	ask.qclass = qclass;
	ask.local_alias = NULL;
	log_query_info(VERB_ALGO, "generate request", &ask);
	/* enable valrec flag to avoid recursion to the same validation
	 * routine, this lookup is simply a lookup. DLVs need validation */
	if(qtype == LDNS_RR_TYPE_DLV)
		valrec = 0;
	else valrec = 1;

	fptr_ok(fptr_whitelist_modenv_detect_cycle(qstate->env->detect_cycle));
	if((*qstate->env->detect_cycle)(qstate, &ask,
		(uint16_t)(BIT_RD|flags), 0, valrec)) {
		verbose(VERB_ALGO, "Could not generate request: cycle detected");
		return 0;
	}

	if(detached) {
		struct mesh_state* sub = NULL;
		fptr_ok(fptr_whitelist_modenv_add_sub(
			qstate->env->add_sub));
		if(!(*qstate->env->add_sub)(qstate, &ask, 
			(uint16_t)(BIT_RD|flags), 0, valrec, newq, &sub)){
			log_err("Could not generate request: out of memory");
			return 0;
		}
	}
	else {
		fptr_ok(fptr_whitelist_modenv_attach_sub(
			qstate->env->attach_sub));
		if(!(*qstate->env->attach_sub)(qstate, &ask, 
			(uint16_t)(BIT_RD|flags), 0, valrec, newq)){
			log_err("Could not generate request: out of memory");
			return 0;
		}
	}
	/* newq; validator does not need state created for that
	 * query, and its a 'normal' for iterator as well */
	if(*newq) {
		/* add our blacklist to the query blacklist */
		sock_list_merge(&(*newq)->blacklist, (*newq)->region,
			vq->chain_blacklist);
	}
	qstate->ext_state[id] = module_wait_subquery;
	return 1;
}
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
struct val_qstate {scalar_t__ restart_count; void* state; struct key_entry_key* key_entry; int /*<<< orphan*/ * chain_blacklist; int /*<<< orphan*/ * empty_DS_name; int /*<<< orphan*/  ds_rrset; int /*<<< orphan*/  empty_DS_len; } ;
struct sock_list {int dummy; } ;
struct query_info {int /*<<< orphan*/  qname; int /*<<< orphan*/  qname_len; } ;
struct module_qstate {int /*<<< orphan*/ * errinf; int /*<<< orphan*/  region; } ;
struct key_entry_key {int dummy; } ;
struct dns_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ VAL_MAX_RESTART_COUNT ; 
 void* VAL_VALIDATE_STATE ; 
 int /*<<< orphan*/  ds_response_to_ke (struct module_qstate*,struct val_qstate*,int,int,struct dns_msg*,struct query_info*,struct key_entry_key**) ; 
 int /*<<< orphan*/  errinf_dname (struct module_qstate*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errinf_origin (struct module_qstate*,struct sock_list*) ; 
 int /*<<< orphan*/  key_entry_get_rrset (struct key_entry_key*,int /*<<< orphan*/ ) ; 
 scalar_t__ key_entry_isbad (struct key_entry_key*) ; 
 scalar_t__ key_entry_isgood (struct key_entry_key*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/ * regional_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_blacklist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,struct sock_list*,int) ; 

__attribute__((used)) static void
process_ds_response(struct module_qstate* qstate, struct val_qstate* vq,
	int id, int rcode, struct dns_msg* msg, struct query_info* qinfo,
	struct sock_list* origin)
{
	struct key_entry_key* dske = NULL;
	uint8_t* olds = vq->empty_DS_name;
	vq->empty_DS_name = NULL;
	if(!ds_response_to_ke(qstate, vq, id, rcode, msg, qinfo, &dske)) {
			log_err("malloc failure in process_ds_response");
			vq->key_entry = NULL; /* make it error */
			vq->state = VAL_VALIDATE_STATE;
			return;
	}
	if(dske == NULL) {
		vq->empty_DS_name = regional_alloc_init(qstate->region,
			qinfo->qname, qinfo->qname_len);
		if(!vq->empty_DS_name) {
			log_err("malloc failure in empty_DS_name");
			vq->key_entry = NULL; /* make it error */
			vq->state = VAL_VALIDATE_STATE;
			return;
		}
		vq->empty_DS_len = qinfo->qname_len;
		vq->chain_blacklist = NULL;
		/* ds response indicated that we aren't on a delegation point.
		 * Keep the forState.state on FINDKEY. */
	} else if(key_entry_isgood(dske)) {
		vq->ds_rrset = key_entry_get_rrset(dske, qstate->region);
		if(!vq->ds_rrset) {
			log_err("malloc failure in process DS");
			vq->key_entry = NULL; /* make it error */
			vq->state = VAL_VALIDATE_STATE;
			return;
		}
		vq->chain_blacklist = NULL; /* fresh blacklist for next part*/
		/* Keep the forState.state on FINDKEY. */
	} else if(key_entry_isbad(dske) 
		&& vq->restart_count < VAL_MAX_RESTART_COUNT) {
		vq->empty_DS_name = olds;
		val_blacklist(&vq->chain_blacklist, qstate->region, origin, 1);
		qstate->errinf = NULL;
		vq->restart_count++;
	} else {
		if(key_entry_isbad(dske)) {
			errinf_origin(qstate, origin);
			errinf_dname(qstate, "for DS", qinfo->qname);
		}
		/* NOTE: the reason for the DS to be not good (that is, 
		 * either bad or null) should have been logged by 
		 * dsResponseToKE. */
		vq->key_entry = dske;
		/* The FINDKEY phase has ended, so move on. */
		vq->state = VAL_VALIDATE_STATE;
	}
}
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
struct reply_info {int dummy; } ;
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
struct module_qstate {struct edns_option* edns_opts_front_out; } ;
struct inplace_cb {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  id; scalar_t__ cb; struct inplace_cb* next; } ;
struct edns_option {int dummy; } ;
struct edns_data {struct edns_option* opt_list; } ;
struct comm_reply {int dummy; } ;
typedef  int /*<<< orphan*/  (* inplace_cb_reply_func_type ) (struct query_info*,struct module_qstate*,struct reply_info*,int,struct edns_data*,struct edns_option**,struct comm_reply*,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  enum inplace_cb_list_type { ____Placeholder_inplace_cb_list_type } inplace_cb_list_type ;

/* Variables and functions */
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_inplace_cb_reply_generic (int /*<<< orphan*/  (*) (struct query_info*,struct module_qstate*,struct reply_info*,int,struct edns_data*,struct edns_option**,struct comm_reply*,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int) ; 
 int /*<<< orphan*/  stub1 (struct query_info*,struct module_qstate*,struct reply_info*,int,struct edns_data*,struct edns_option**,struct comm_reply*,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inplace_cb_reply_call_generic(
    struct inplace_cb* callback_list, enum inplace_cb_list_type type,
	struct query_info* qinfo, struct module_qstate* qstate,
	struct reply_info* rep, int rcode, struct edns_data* edns,
	struct comm_reply* repinfo, struct regional* region)
{
	struct inplace_cb* cb;
	struct edns_option* opt_list_out = NULL;
#if defined(EXPORT_ALL_SYMBOLS)
	(void)type; /* param not used when fptr_ok disabled */
#endif
	if(qstate)
		opt_list_out = qstate->edns_opts_front_out;
	for(cb=callback_list; cb; cb=cb->next) {
		fptr_ok(fptr_whitelist_inplace_cb_reply_generic(
			(inplace_cb_reply_func_type*)cb->cb, type));
		(void)(*(inplace_cb_reply_func_type*)cb->cb)(qinfo, qstate, rep,
			rcode, edns, &opt_list_out, repinfo, region, cb->id, cb->cb_arg);
	}
	edns->opt_list = opt_list_out;
	return 1;
}
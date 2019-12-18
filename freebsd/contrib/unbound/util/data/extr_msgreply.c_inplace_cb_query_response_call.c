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
struct module_qstate {int dummy; } ;
struct module_env {struct inplace_cb** inplace_cb_lists; } ;
struct inplace_cb {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  id; scalar_t__ cb; struct inplace_cb* next; } ;
struct dns_msg {int dummy; } ;
typedef  int /*<<< orphan*/  (* inplace_cb_query_response_func_type ) (struct module_qstate*,struct dns_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_inplace_cb_query_response (int /*<<< orphan*/  (*) (struct module_qstate*,struct dns_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 size_t inplace_cb_query_response ; 
 int /*<<< orphan*/  stub1 (struct module_qstate*,struct dns_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int inplace_cb_query_response_call(struct module_env* env,
	struct module_qstate* qstate, struct dns_msg* response) {
	struct inplace_cb* cb =
		env->inplace_cb_lists[inplace_cb_query_response];
	for(; cb; cb=cb->next) {
		fptr_ok(fptr_whitelist_inplace_cb_query_response(
			(inplace_cb_query_response_func_type*)cb->cb));
		(void)(*(inplace_cb_query_response_func_type*)cb->cb)(qstate,
			response, cb->id, cb->cb_arg);
	}
	return 1;
}
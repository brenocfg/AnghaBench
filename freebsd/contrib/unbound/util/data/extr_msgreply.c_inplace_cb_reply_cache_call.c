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
struct module_qstate {int dummy; } ;
struct module_env {int /*<<< orphan*/ * inplace_cb_lists; } ;
struct edns_data {int dummy; } ;
struct comm_reply {int dummy; } ;

/* Variables and functions */
 size_t inplace_cb_reply_cache ; 
 int inplace_cb_reply_call_generic (int /*<<< orphan*/ ,size_t,struct query_info*,struct module_qstate*,struct reply_info*,int,struct edns_data*,struct comm_reply*,struct regional*) ; 

int inplace_cb_reply_cache_call(struct module_env* env,
	struct query_info* qinfo, struct module_qstate* qstate,
	struct reply_info* rep, int rcode, struct edns_data* edns,
	struct comm_reply* repinfo, struct regional* region)
{
	return inplace_cb_reply_call_generic(
		env->inplace_cb_lists[inplace_cb_reply_cache], inplace_cb_reply_cache,
		qinfo, qstate, rep, rcode, edns, repinfo, region);
}
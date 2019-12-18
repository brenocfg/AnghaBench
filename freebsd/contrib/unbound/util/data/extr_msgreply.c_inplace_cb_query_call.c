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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
struct module_qstate {int dummy; } ;
struct module_env {struct inplace_cb** inplace_cb_lists; } ;
struct inplace_cb {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  id; scalar_t__ cb; struct inplace_cb* next; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  (* inplace_cb_query_func_type ) (struct query_info*,int /*<<< orphan*/ ,struct module_qstate*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_inplace_cb_query (int /*<<< orphan*/  (*) (struct query_info*,int /*<<< orphan*/ ,struct module_qstate*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 size_t inplace_cb_query ; 
 int /*<<< orphan*/  stub1 (struct query_info*,int /*<<< orphan*/ ,struct module_qstate*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int inplace_cb_query_call(struct module_env* env, struct query_info* qinfo,
	uint16_t flags, struct sockaddr_storage* addr, socklen_t addrlen,
	uint8_t* zone, size_t zonelen, struct module_qstate* qstate,
	struct regional* region)
{
	struct inplace_cb* cb = env->inplace_cb_lists[inplace_cb_query];
	for(; cb; cb=cb->next) {
		fptr_ok(fptr_whitelist_inplace_cb_query(
			(inplace_cb_query_func_type*)cb->cb));
		(void)(*(inplace_cb_query_func_type*)cb->cb)(qinfo, flags,
			qstate, addr, addrlen, zone, zonelen, region,
			cb->id, cb->cb_arg);
	}
	return 1;
}
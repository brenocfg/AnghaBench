#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_query_type {scalar_t__ on_free; scalar_t__ on_alarm; scalar_t__ on_answer; } ;
struct rpc_query {int dummy; } ;
struct TYPE_5__ {scalar_t__* fun_pos; scalar_t__ funs; } ;
struct TYPE_8__ {TYPE_1__ methods; } ;
struct TYPE_7__ {TYPE_2__* h; int /*<<< orphan*/  in_type; int /*<<< orphan*/ * remote_pid; } ;
struct TYPE_6__ {double custom_timeout; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 TYPE_4__* CC ; 
 TYPE_3__* CQ ; 
 size_t RPC_FUN_QUERY_ON_ALARM ; 
 size_t RPC_FUN_QUERY_ON_ANSWER ; 
 size_t RPC_FUN_QUERY_ON_FREE ; 
 struct rpc_query* create_rpc_query (long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_query_type,double) ; 

struct rpc_query *default_create_rpc_query (long long new_qid) {
  struct rpc_query_type qt;
  qt.on_answer = CC->methods.funs + CC->methods.fun_pos[RPC_FUN_QUERY_ON_ANSWER];
  qt.on_alarm = CC->methods.funs + CC->methods.fun_pos[RPC_FUN_QUERY_ON_ALARM];
  qt.on_free = CC->methods.funs + CC->methods.fun_pos[RPC_FUN_QUERY_ON_FREE];
  return create_rpc_query (new_qid, *CQ->remote_pid, CQ->h->qid, CQ->in_type, /*CQ->in,*/ qt, CQ->h->custom_timeout * 0.001);
}
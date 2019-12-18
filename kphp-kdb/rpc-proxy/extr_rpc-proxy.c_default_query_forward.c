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
struct rpc_cluster_bucket {TYPE_2__* methods; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fun_pos; } ;
struct TYPE_6__ {TYPE_1__ methods; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_actor ) (struct rpc_cluster_bucket*) ;void* (* get_conn ) (struct rpc_cluster_bucket*) ;} ;

/* Variables and functions */
 TYPE_3__* CC ; 
 size_t RPC_FUN_ON_NET_FAIL ; 
 int RPC_FUN_START (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  assert (struct rpc_cluster_bucket*) ; 
 int /*<<< orphan*/  default_query_forward_conn (struct rpc_cluster_bucket*,void*,int /*<<< orphan*/ ,long long,int) ; 
 void* stub1 (struct rpc_cluster_bucket*) ; 
 int /*<<< orphan*/  stub2 (struct rpc_cluster_bucket*) ; 
 int /*<<< orphan*/  tl_fetch_error () ; 

int default_query_forward (struct rpc_cluster_bucket *B, long long new_qid) {
  assert (B);
  if (!tl_fetch_error ()) {
    void *conn = B->methods->get_conn (B);
    if (!conn) {
      void *E[2];
      E[0] = B;
      E[1] = &new_qid;
      return RPC_FUN_START(CC->methods.fun_pos[RPC_FUN_ON_NET_FAIL], E);
    } else {
      default_query_forward_conn (B, conn, B->methods->get_actor (B), new_qid, 1);
      return 0;
    }
  } else {
    return -1;
  }
}
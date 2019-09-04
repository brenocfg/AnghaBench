#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rpc_cluster_bucket {TYPE_1__* methods; } ;
struct rpc_cluster {int tot_buckets; struct rpc_cluster_bucket* buckets; } ;
struct TYPE_8__ {int s_addr; } ;
struct conn_target {int custom_field; int port; TYPE_2__ target; int /*<<< orphan*/  ready_outbound_connections; int /*<<< orphan*/  min_connections; } ;
struct TYPE_10__ {int (* forward ) () ;int /*<<< orphan*/ * fun_pos; } ;
struct TYPE_12__ {TYPE_4__ methods; } ;
struct TYPE_11__ {TYPE_3__* h; int /*<<< orphan*/  remote_pid; int /*<<< orphan*/  in_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  qid; } ;
struct TYPE_7__ {int (* get_host ) (struct rpc_cluster_bucket*) ;int (* get_port ) (struct rpc_cluster_bucket*) ;int /*<<< orphan*/  (* get_actor ) (struct rpc_cluster_bucket*) ;} ;

/* Variables and functions */
 TYPE_6__* CC ; 
 TYPE_5__* CQ ; 
 size_t RPC_FUN_PREFORWARD_CHECK ; 
 size_t RPC_FUN_PREFORWARD_EDIT ; 
 size_t RPC_FUN_PREFORWARD_VIEW ; 
 int RPC_FUN_START (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TL_ENGINE_NOP 134 
#define  TL_ENGINE_STAT 133 
 int TL_MAYBE_FALSE ; 
 int TL_MAYBE_TRUE ; 
#define  TL_RPC_PROXY_GET_BAD_TARGETS 132 
#define  TL_RPC_PROXY_GET_CLUSTERS 131 
#define  TL_RPC_PROXY_GET_CLUSTER_SERVERS 130 
#define  TL_RPC_PROXY_GET_CLUSTER_SIZE 129 
#define  TL_RPC_PROXY_GET_CLUSTER_STATS 128 
 int TL_TRUE ; 
 int TL_VECTOR ; 
 struct conn_target* Targets ; 
 int allocated_targets ; 
 int /*<<< orphan*/  assert (struct conn_target*) ; 
 struct rpc_cluster* get_cluster_by_id (long long) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  store_cluster_stats (struct rpc_cluster*) ; 
 int /*<<< orphan*/  store_stats () ; 
 int stub1 (struct rpc_cluster_bucket*) ; 
 int stub2 (struct rpc_cluster_bucket*) ; 
 int /*<<< orphan*/  stub3 (struct rpc_cluster_bucket*) ; 
 int stub4 () ; 
 int /*<<< orphan*/  tl_dump_clusters () ; 
 int /*<<< orphan*/  tl_fetch_end () ; 
 int /*<<< orphan*/  tl_fetch_int () ; 
 long long tl_fetch_long () ; 
 int tl_fetch_lookup_int () ; 
 int /*<<< orphan*/  tl_init_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int* tl_store_get_ptr (int) ; 
 int /*<<< orphan*/  tl_store_int (int) ; 
 int /*<<< orphan*/  tl_store_long (int /*<<< orphan*/ ) ; 

int do_forward (void) {
  int op = tl_fetch_lookup_int ();
  long long t;
  struct rpc_cluster *C;
  int i;
  switch (op) {
  case TL_ENGINE_NOP:
    tl_fetch_int ();
    tl_fetch_end ();
    //tl_store_init_any_keep_error (CQ->in_type, CQ->in, CQ->h->qid);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);
    tl_store_int (TL_TRUE);
    tl_store_end ();
    return 0;
  case TL_RPC_PROXY_GET_CLUSTERS:
    tl_fetch_int ();
    tl_fetch_end ();
    //tl_store_init_any_keep_error (CQ->in_type, CQ->in, CQ->h->qid);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);
    tl_dump_clusters ();
    tl_store_end ();
    return 0;
  case TL_RPC_PROXY_GET_CLUSTER_SIZE:
    tl_fetch_int ();
    t = tl_fetch_long ();
    tl_fetch_end ();
    //tl_store_init_any_keep_error (CQ->in_type, CQ->in, CQ->h->qid);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);

    C = get_cluster_by_id (t);
    if (!C) {
      tl_store_int (TL_MAYBE_FALSE);
    } else {
      tl_store_int (TL_MAYBE_TRUE);
      tl_store_int (C->tot_buckets);
    }
    tl_store_end ();
    return 0;
  case TL_RPC_PROXY_GET_CLUSTER_SERVERS:
    tl_fetch_int ();
    t = tl_fetch_long ();
    tl_fetch_end ();
    //tl_store_init_any_keep_error (CQ->in_type, CQ->in, CQ->h->qid);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);
    C = get_cluster_by_id (t);
    if (!C) {
      tl_store_int (TL_MAYBE_FALSE);
    } else {
      tl_store_int (TL_MAYBE_TRUE);
      tl_store_int (C->tot_buckets);
      for (i = 0; i < C->tot_buckets; i++) {
        struct rpc_cluster_bucket *B = &C->buckets[i];
        tl_store_int (B->methods->get_host (B));
        tl_store_int (B->methods->get_port (B)); 
        tl_store_long (B->methods->get_actor (B)); 
      }
    }
    tl_store_end ();
    return 0;
  case TL_RPC_PROXY_GET_CLUSTER_STATS:
    tl_fetch_int ();
    t = tl_fetch_long ();
    tl_fetch_end ();
    //tl_store_init_any_keep_error (CQ->in_type, CQ->in, CQ->h->qid);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);
    C = get_cluster_by_id (t);
    if (!C) {
      tl_store_int (TL_MAYBE_FALSE);
    } else {
      tl_store_int (TL_MAYBE_TRUE);
      store_cluster_stats (C);
    }
    tl_store_end ();
    return 0;
  case TL_RPC_PROXY_GET_BAD_TARGETS:
    tl_fetch_int ();
    tl_fetch_end ();
    //tl_store_init_any_keep_error (CQ->in_type, CQ->in, CQ->h->qid);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);
    tl_store_int (TL_VECTOR);
    {
      int *count = tl_store_get_ptr (4);
      *count = 0;
      int i;
      for (i = 0; i < allocated_targets; i++) {
        struct conn_target *S = &Targets[i];
        assert (S);
        if (S->min_connections > 0 && !S->ready_outbound_connections) {
          if (S->target.s_addr) {
            int x =  (S->target.s_addr);            
            tl_store_int (ntohl (x));
          } else {
            tl_store_int (S->custom_field);
          }
          tl_store_int (S->port);
          (*count) ++;
        }
      }
    }
    tl_store_end ();
    return 0;
  case TL_ENGINE_STAT:
    tl_fetch_int ();
    tl_fetch_end ();
    //tl_store_init_any_keep_error (CQ->in_type, CQ->in, CQ->h->qid);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);
    store_stats ();
    tl_store_end ();
    return 0;
  }
  int x;
  x = RPC_FUN_START(CC->methods.fun_pos[RPC_FUN_PREFORWARD_CHECK], 0);
  if (x < 0) { return x; }
  x = RPC_FUN_START(CC->methods.fun_pos[RPC_FUN_PREFORWARD_EDIT], 0);
  if (x < 0) { return x; }
  x = RPC_FUN_START(CC->methods.fun_pos[RPC_FUN_PREFORWARD_VIEW], 0);
  if (x < 0) { return x; }
  return CC->methods.forward ();
}
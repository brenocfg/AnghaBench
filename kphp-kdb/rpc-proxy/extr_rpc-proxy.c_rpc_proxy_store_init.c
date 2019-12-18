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
struct rpc_cluster_bucket {TYPE_1__* methods; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_store ) (struct rpc_cluster_bucket*,void*,long long) ;void* (* get_conn ) (struct rpc_cluster_bucket*) ;} ;

/* Variables and functions */
 void* stub1 (struct rpc_cluster_bucket*) ; 
 int /*<<< orphan*/  stub2 (struct rpc_cluster_bucket*,void*,long long) ; 

int rpc_proxy_store_init (struct rpc_cluster_bucket *B, long long new_qid) {
  void *conn = B->methods->get_conn (B);
  if (!conn) {
    return 0;
  } else {
    B->methods->init_store (B, conn, new_qid);
    return 1;
  }
  /*
  if (CC->proto == PROTO_TCP) {
    struct rpc_target *S = rpc_target_lookup_target (B->T);
    struct connection *d = rpc_target_choose_connection (S, 0);
    if (!d) {
      return 0;
    }
    tl_store_init (d, new_qid);
    return 1;
  } else {
    struct udp_target *S = udp_target_set_choose_target (B->S);
    if (!S || S->state == udp_failed) {
      return 0;
    }
    tl_store_init_raw_msg (S, new_qid);
    return 1;
  }*/
}
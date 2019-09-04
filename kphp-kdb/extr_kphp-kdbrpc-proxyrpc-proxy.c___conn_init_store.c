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
struct rpc_cluster_bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  tcp_buffers ; 
 int /*<<< orphan*/  tl_store_init (void*,long long) ; 
 int /*<<< orphan*/  tl_store_init_tcp_raw_msg (void*,long long) ; 

void __conn_init_store (struct rpc_cluster_bucket *B, void *c, long long qid) {
  assert (c);
  if (!tcp_buffers) {
    tl_store_init (c, qid);
  } else {
    tl_store_init_tcp_raw_msg (c, qid);
  }
}
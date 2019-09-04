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
struct udp_target {int dummy; } ;
struct rpc_cluster_bucket {int /*<<< orphan*/  S; } ;

/* Variables and functions */
 struct udp_target* udp_target_set_choose_target (int /*<<< orphan*/ ) ; 

int __udp_get_multi_conn (struct rpc_cluster_bucket *B, void **buf, int n) {
  struct udp_target *S = udp_target_set_choose_target (B->S);
  if (!S) { return 0; }
  *buf = (void *)1l;
  return 1;
}
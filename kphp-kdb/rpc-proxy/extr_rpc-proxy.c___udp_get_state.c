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
struct udp_target {scalar_t__ state; } ;
struct rpc_cluster_bucket {int /*<<< orphan*/  S; } ;

/* Variables and functions */
 scalar_t__ udp_ok ; 
 scalar_t__ udp_stopped ; 
 struct udp_target* udp_target_set_choose_target (int /*<<< orphan*/ ) ; 
 scalar_t__ udp_unknown ; 

int __udp_get_state (struct rpc_cluster_bucket *B) {
  struct udp_target *S = udp_target_set_choose_target (B->S);
  if (!S) { return -1; }
  if (S->state == udp_ok) { 
    return 1;
  } else if (S->state == udp_stopped || S->state == udp_unknown) {
    return 0;
  } else {
    return -1;
  }
}
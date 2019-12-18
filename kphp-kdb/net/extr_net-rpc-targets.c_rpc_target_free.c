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
struct rpc_target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_target_tree ; 
 int /*<<< orphan*/  tree_delete_rpc_target (int /*<<< orphan*/ ,struct rpc_target*) ; 
 int /*<<< orphan*/  zfree (struct rpc_target*,int) ; 

void rpc_target_free (struct rpc_target *S) {
  rpc_target_tree = tree_delete_rpc_target (rpc_target_tree, S);
  zfree (S, sizeof (*S));
}
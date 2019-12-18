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
struct rpc_queue {int /*<<< orphan*/  completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  tree_clear_qid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zzfree (struct rpc_queue*,int) ; 

void free_queue (struct rpc_queue *Q) {
  tree_clear_qid (Q->completed);
  zzfree (Q, sizeof (*Q));
}
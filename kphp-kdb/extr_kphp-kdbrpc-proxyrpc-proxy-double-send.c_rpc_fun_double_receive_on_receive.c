#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* h; int /*<<< orphan*/ * remote_pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 TYPE_2__* CQ ; 
 int /*<<< orphan*/  RPC_FUN_NEXT ; 
 int /*<<< orphan*/  assert (int) ; 
 int double_receive_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int rpc_fun_double_receive_on_receive (void **IP, void **Data) {
  int t = double_receive_add (*CQ->remote_pid, CQ->h->qid);
  assert (t >= 0);
  if (!t) {
    vkprintf (2, "Duplicate query. Skipping.");
    return -1;
  }
  RPC_FUN_NEXT;
}
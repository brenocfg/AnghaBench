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
struct rpc_query {void** extra; } ;
struct gather {int tot_num; TYPE_3__* methods; int /*<<< orphan*/  wait_num; int /*<<< orphan*/  errors_num; int /*<<< orphan*/  received_num; TYPE_1__* List; } ;
struct TYPE_8__ {TYPE_2__* h; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* on_end ) (struct gather*) ;int /*<<< orphan*/  (* on_error ) (struct gather*,int) ;int /*<<< orphan*/  (* on_answer ) (struct gather*,int) ;} ;
struct TYPE_6__ {scalar_t__ op; } ;
struct TYPE_5__ {int bytes; } ;

/* Variables and functions */
 TYPE_4__* CQ ; 
 scalar_t__ RPC_REQ_RESULT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  default_gather_on_answer (struct gather*,int) ; 
 int /*<<< orphan*/  default_gather_on_error (struct gather*,int) ; 
 int /*<<< orphan*/  stub1 (struct gather*,int) ; 
 int /*<<< orphan*/  stub2 (struct gather*,int) ; 
 int /*<<< orphan*/  stub3 (struct gather*) ; 

void merge_on_answer (struct rpc_query *q) {
  void **t = q->extra;
  struct gather *G = t[0];
  int num = (long)t[1];
  assert (num >= 0 && num <= G->tot_num - 1);
  assert (G->List[num].bytes == -2);
  G->wait_num --;
  if (CQ->h->op == RPC_REQ_RESULT) {
    G->received_num ++;
    if (G->methods->on_answer) {
      G->methods->on_answer (G, num);
    } else {
      default_gather_on_answer (G, num);
    }
  } else {
    G->errors_num ++;
    if (G->methods->on_error) {
      G->methods->on_error (G, num);
    } else {
      default_gather_on_error (G, num);
    }
  }
  if (!G->wait_num) {
    G->methods->on_end (G);
  }
}
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
struct rpc_query {void** extra; } ;
struct gather {int tot_num; TYPE_2__* methods; int /*<<< orphan*/  wait_num; int /*<<< orphan*/  timeouted_num; TYPE_1__* List; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_end ) (struct gather*) ;int /*<<< orphan*/  (* on_timeout ) (struct gather*,int) ;} ;
struct TYPE_3__ {int bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (struct gather*,int) ; 
 int /*<<< orphan*/  stub2 (struct gather*) ; 

void merge_on_alarm (struct rpc_query *q) {
  void **t = q->extra;
  struct gather *G = t[0];
  int num = (long)t[1];
  assert (num >= 0 && num <= G->tot_num - 1);
  assert (G->List[num].bytes == -2);
  G->timeouted_num ++;
  G->wait_num --;
  if (G->methods->on_timeout) {
    G->methods->on_timeout (G, num);
  }
  if (!G->wait_num) {
    G->methods->on_end (G);
  }
}
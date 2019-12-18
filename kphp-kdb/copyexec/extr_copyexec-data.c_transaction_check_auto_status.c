#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 TYPE_1__ auto_running_list ; 
 int /*<<< orphan*/  check_is_running (TYPE_1__*) ; 
 int /*<<< orphan*/  transaction_finish_execution (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int transaction_check_auto_status (void) {
  int res = 0;
  transaction_t *T, *W;

  for (T = auto_running_list.next; T != &auto_running_list; T = W) {
    W = T->next;
    if (!check_is_running (T)) {
      vkprintf (4, "transaction_check_auto_status: call transaction_finish_execution\n");
      transaction_finish_execution (T, 1);
    }
  }
  if (res > 0) {
    vkprintf (3, "transaction_check_auto_status: %d transaction(s) finished.\n", res);
  }
  return res;
}
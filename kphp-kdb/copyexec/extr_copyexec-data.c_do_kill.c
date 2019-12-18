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
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_is_running (TYPE_1__*) ; 
 TYPE_1__* get_transaction_f (int,int /*<<< orphan*/ ) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int) ; 
 int transaction_wait (TYPE_1__*) ; 

__attribute__((used)) static int do_kill (int signal, int transaction_id) {
  transaction_t *T = get_transaction_f (transaction_id, 0);
  if (T == NULL) {
    return 0;
  }

  if (!check_is_running (T)) {
    return 0;
  }

  if (kill (T->pid, signal) < 0) {
    return 0;
  }

  return transaction_wait (T);
}
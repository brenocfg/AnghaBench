#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  transaction_id; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  check_is_running (TYPE_1__*) ; 
 int kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transaction_cancel (transaction_t *T) {
  if (!check_is_running (T)) {
    vkprintf (3, "transaction_cancel: tr%d has terminated.\n", T->transaction_id);
    return 0;
  }
  int r = kill (T->pid, SIGUSR2);
  if (r < 0) {
    vkprintf (2, "transaction_cancel: kill (%d) failed. %m\n", T->pid);
  }
  return r;
}
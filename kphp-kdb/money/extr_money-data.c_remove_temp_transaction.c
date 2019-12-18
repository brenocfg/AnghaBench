#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* th_next; TYPE_1__* th_prev; } ;
typedef  TYPE_2__ transaction_t ;
struct TYPE_4__ {struct TYPE_4__* th_prev; struct TYPE_4__* th_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int remove_temp_transaction (transaction_t *T) {
  assert (T->th_next && T->th_prev);
  T->th_prev->th_next = T->th_next;
  T->th_next->th_prev = T->th_prev;
  T->th_prev = T->th_next = 0;
  return 0;
}
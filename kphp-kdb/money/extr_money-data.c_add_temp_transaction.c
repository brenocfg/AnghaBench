#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* th_prev; struct TYPE_4__* th_next; int /*<<< orphan*/  temp_id; } ;
typedef  TYPE_1__ transaction_t ;
struct TYPE_5__ {TYPE_1__* th_first; } ;

/* Variables and functions */
 TYPE_3__* TrTempHash ; 
 int /*<<< orphan*/  assert (int) ; 
 int transaction_temp_bucket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_temp_transaction (transaction_t *T) {
  int b = transaction_temp_bucket (T->temp_id);
  assert (!T->th_next && !T->th_prev);

  T->th_next = TrTempHash[b].th_first;
  T->th_prev = (void *) &TrTempHash[b];
  TrTempHash[b].th_first->th_prev = T;
  TrTempHash[b].th_first = T;

  return 0;
}
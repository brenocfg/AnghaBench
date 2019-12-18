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
struct TYPE_5__ {int long_lock_heap_pos; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 TYPE_1__** LH ; 
 int LHN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lock_heap_adjust (int,TYPE_1__*) ; 
 int locked_long_transactions ; 

__attribute__((used)) static void remove_from_lock_heap (transaction_t *T) {
  int i = T->long_lock_heap_pos;
  assert (i > 0 && i <= LHN && LH[i] == T);
  T->long_lock_heap_pos = 0;
  locked_long_transactions = --LHN;
  if (i <= LHN) {
    lock_heap_adjust (i, LH[LHN+1]);
  }
}
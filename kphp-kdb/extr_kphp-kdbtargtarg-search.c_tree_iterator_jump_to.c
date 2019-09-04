#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mult; } ;
struct tree_iterator {int pos; TYPE_1__ TS; int /*<<< orphan*/  mult; int /*<<< orphan*/  jump_to; } ;
typedef  scalar_t__ iterator_t ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  empty_iterator_jump_to ; 
 int tree_subiterator_jump_to (TYPE_1__*,int) ; 

int tree_iterator_jump_to (iterator_t I, int req_pos) {
  struct tree_iterator *TI = (struct tree_iterator *) I;
  int res = tree_subiterator_jump_to (&TI->TS, req_pos);
  if (res == INFTY) {
    TI->jump_to = empty_iterator_jump_to;
  } else {
    assert ((TI->mult = TI->TS.mult) > 0);
  }
  return TI->pos = res;
}
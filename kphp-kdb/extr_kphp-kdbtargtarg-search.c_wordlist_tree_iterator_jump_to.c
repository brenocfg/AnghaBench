#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pos; scalar_t__ mult; } ;
struct TYPE_6__ {int pos; scalar_t__ mult; } ;
struct wordlist_tree_iterator {scalar_t__ mult; int pos; TYPE_1__ WS; TYPE_3__ TS; int /*<<< orphan*/  jump_to; } ;
typedef  scalar_t__ iterator_t ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  empty_iterator_jump_to ; 
 int tree_subiterator_jump_to (TYPE_3__*,int) ; 
 int tree_subiterator_next (TYPE_3__*) ; 
 int wordlist_subiterator_jump_to (TYPE_1__*,int) ; 
 int wordlist_subiterator_next (TYPE_1__*) ; 

int wordlist_tree_iterator_jump_to (iterator_t I, int req_pos) {
  struct wordlist_tree_iterator *WTI = (struct wordlist_tree_iterator *) I;
  int a = WTI->TS.pos;
  if (a < req_pos) {
    a = tree_subiterator_jump_to (&WTI->TS, req_pos);
  }
  int b = WTI->WS.pos;
  if (b < req_pos) {
    b = wordlist_subiterator_jump_to (&WTI->WS, req_pos);
  }
  while (1) {
    if (a < b) {
      assert ((WTI->mult = WTI->TS.mult) > 0);
      return WTI->pos = a;
    } else if (a > b) {
      assert ((WTI->mult = WTI->WS.mult) > 0);
      return WTI->pos = b;
    } else if (a == INFTY) {
      WTI->jump_to = empty_iterator_jump_to;
      return WTI->pos = a;
    } else if (WTI->WS.mult + WTI->TS.mult > 0) {
      WTI->mult = WTI->WS.mult + WTI->TS.mult;
      return WTI->pos = a;
    }
    a = tree_subiterator_next (&WTI->TS);
    b = wordlist_subiterator_next (&WTI->WS);
  }
}
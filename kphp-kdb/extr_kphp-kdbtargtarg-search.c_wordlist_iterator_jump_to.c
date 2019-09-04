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
struct wordlist_iterator {int pos; TYPE_1__ WS; int /*<<< orphan*/  mult; int /*<<< orphan*/  jump_to; } ;
typedef  scalar_t__ iterator_t ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  empty_iterator_jump_to ; 
 int wordlist_subiterator_jump_to (TYPE_1__*,int) ; 

int wordlist_iterator_jump_to (iterator_t I, int req_pos) {
  struct wordlist_iterator *WI = (struct wordlist_iterator *) I;
  int res = wordlist_subiterator_jump_to (&WI->WS, req_pos);
  if (res == INFTY) {
    WI->jump_to = empty_iterator_jump_to;
  } else {
    assert ((WI->mult = WI->WS.mult) > 0);
  }
  return WI->pos = res;
}
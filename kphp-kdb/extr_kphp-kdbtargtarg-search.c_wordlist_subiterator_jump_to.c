#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wordlist_subiterator {int pos; int /*<<< orphan*/  mult; int /*<<< orphan*/  mdec; } ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int mlist_forward_decode_idx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int wordlist_subiterator_next (struct wordlist_subiterator*) ; 

int wordlist_subiterator_jump_to (struct wordlist_subiterator *WI, int req_pos) {
  if (req_pos == WI->pos + 1) {
    return wordlist_subiterator_next (WI);
  } else {
    assert (req_pos > WI->pos);
    int res = mlist_forward_decode_idx (WI->mdec, req_pos, &WI->mult);
    return WI->pos = (res < 0x7fffffff ? res : INFTY);
  }
}
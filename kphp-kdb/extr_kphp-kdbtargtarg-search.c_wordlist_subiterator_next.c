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
 int mlist_decode_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int wordlist_subiterator_next (struct wordlist_subiterator *WI) {
  int res = mlist_decode_pair (WI->mdec, &WI->mult);
  return WI->pos = (res < 0x7fffffff ? res : INFTY);
}
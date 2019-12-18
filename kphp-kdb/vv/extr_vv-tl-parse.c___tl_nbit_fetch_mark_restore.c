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
typedef  int /*<<< orphan*/  nb_iterator_t ;

/* Variables and functions */
 scalar_t__ TL_IN_MARK ; 
 int TL_IN_MARK_POS ; 
 int /*<<< orphan*/ * TL_IN_NBIT ; 
 int TL_IN_POS ; 
 int TL_IN_REMAINING ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  zfree (scalar_t__,int) ; 

__attribute__((used)) static inline void __tl_nbit_fetch_mark_restore (void) {
  assert (TL_IN_MARK);
  *TL_IN_NBIT = *(nb_iterator_t *)TL_IN_MARK;
  zfree (TL_IN_MARK, sizeof (nb_iterator_t));
  TL_IN_MARK = 0;
  int x = TL_IN_POS - TL_IN_MARK_POS;
  TL_IN_POS -= x;
  TL_IN_REMAINING += x;
}
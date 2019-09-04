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
 int /*<<< orphan*/ * TL_IN_MARK ; 
 int /*<<< orphan*/  TL_IN_MARK_POS ; 
 int /*<<< orphan*/ * TL_IN_NBIT ; 
 int /*<<< orphan*/  TL_IN_POS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * zmalloc (int) ; 

__attribute__((used)) static inline void __tl_nbit_fetch_mark (void) {
  assert (!TL_IN_MARK);
  nb_iterator_t *T = zmalloc (sizeof (*T));
  *T = *TL_IN_NBIT;
  TL_IN_MARK = T;
  TL_IN_MARK_POS = TL_IN_POS;
}
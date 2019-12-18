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

/* Variables and functions */
 int TL_OUT_POS ; 
 int /*<<< orphan*/  _tl_store_raw_data (int*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ tl_store_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tl_store_pad (void) {
  assert (tl_store_check (0) >= 0);
  int x = 0;
  int pad = (-TL_OUT_POS) & 3;
  _tl_store_raw_data (&x, pad);
  return 0;
}
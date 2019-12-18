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
 int /*<<< orphan*/  TL_ERROR_SYNTAX ; 
 int TL_IN_POS ; 
 int TL_IN_REMAINING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ tl_fetch_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_raw_data (int*,int) ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tl_fetch_pad (void) {
  if (tl_fetch_check (0) < 0) {
    return -1;
  }
  int t = 0;
  int pad = (-TL_IN_POS) & 3;
  assert (TL_IN_REMAINING >= pad);
  tl_fetch_raw_data (&t, pad);
  if (t) {
    tl_fetch_set_error ("Padding with non-zeroes", TL_ERROR_SYNTAX);
    return -1;
  }
  return pad;  
}
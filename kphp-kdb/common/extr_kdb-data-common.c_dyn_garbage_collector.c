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
 int* FreeCnt ; 
 int MAX_RECORD_WORDS ; 
 int PTR_INTS ; 
 int* SplitBlocks ; 

void dyn_garbage_collector (void) {
  int i, cval, cmax = -1, cmptr = 0;
  for (i = MAX_RECORD_WORDS + 3; i >= PTR_INTS; i--) {
    cval = FreeCnt[i] * i;
    if (cval > cmax) {
      cmax = cval;
      cmptr = i;
    }
    SplitBlocks[i-PTR_INTS] = cmptr;
  }
}
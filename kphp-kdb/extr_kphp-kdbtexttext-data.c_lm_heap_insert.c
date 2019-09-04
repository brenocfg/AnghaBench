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
 int LN ; 
 int* LX ; 
 int* LY ; 
 int* LZ ; 

void lm_heap_insert (int data_size, int user_id, int last_local_id) {
  int i, j;
  if (data_size <= LX[1]) {
    return;
  }
  i = 1;
  while (1) {
    j = i*2;
    if (j > LN) {
      break;
    }
    if (LX[j] > LX[j+1]) {
      j++;
    }
    if (data_size <= LX[j]) {
      break;
    }
    LX[i] = LX[j];
    LY[i] = LY[j];
    LZ[i] = LZ[j];
    i = j;
  }
  LX[i] = data_size;
  LY[i] = user_id;
  LZ[i] = last_local_id;
}
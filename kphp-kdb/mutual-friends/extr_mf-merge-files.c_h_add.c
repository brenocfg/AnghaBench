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
 int MAXH ; 
 int* h_key ; 
 int* h_val ; 

int h_add (int key, int val) {
  int i = key & (MAXH - 1);
  while (h_key[i] && h_key[i] != key) {
    if (++i == MAXH) {
      i = 0;
    }
  }
  int res = -1;
  if (h_key[i] == 0) {
    h_key[i] = key;
    res = i;
  }

  h_val[i] += val;

  return res;
}
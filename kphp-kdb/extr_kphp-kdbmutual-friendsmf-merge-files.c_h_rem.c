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
 scalar_t__* h_val ; 

void h_rem (int key) {
  int i = key & (MAXH - 1);
  while (h_key[i] && h_key[i] != key) {
    if (++i == MAXH) {
      i = 0;
    }
  }

  h_val[i] = 0;
}
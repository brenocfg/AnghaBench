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

__attribute__((used)) static void reverse_list (int *Res, int sz) {
  int i;
  for (i = 0; i < (sz >> 1); i++) {
    int t = Res[i];
    Res[i] = Res[sz - i - 1];
    Res[sz - i - 1] = t;
  }
}
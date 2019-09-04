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

void dl_kmp (const char *a, int *kmp) {
  if (kmp == NULL) {
    return;
  }
  int i, j = 0;
  kmp[0] = 0;
  for (i = 0; a[i]; i++) {
    while (j && a[i] != a[j]) {
      j = kmp[j];
    }
    if (i != j && a[i] == a[j]) {
      j++;
    }
    kmp[i + 1] = j;
  }
}
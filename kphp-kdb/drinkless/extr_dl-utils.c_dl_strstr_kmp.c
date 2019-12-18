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

char *dl_strstr_kmp (const char *a, int *kmp, const char *b) {
  int i, j = 0;
  for (i = 0; b[i]; i++) {
    while (j && a[j] != b[i])  {
      j = kmp[j];
    }
    if (a[j] == b[i]) {
      j++;
    }

    if (!a[j]) {
      return (char *)(b + i - j + 1);
    }
  }
  return NULL;
}
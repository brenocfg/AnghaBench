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

int ok_cp1251 (char *s, int n) {
  int i;
  for (i = 1; i < n; i++) {
    if (s[i] == (char)0x98) {
      return 0;
    }
  }

  return 1;
}
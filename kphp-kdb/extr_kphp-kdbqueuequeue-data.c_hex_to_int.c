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

int hex_to_int (char *s, int *x) {
  int i;
  *x = 0;
  for (i = 0; i < 8; i++) {
    if ('0' <= s[i] && s[i] <= '9') {
      *x = (*x) * 16 + s[i] - '0';
    } else if ('a' <= s[i] && s[i] <= 'f') {
      *x = (*x) * 16 + s[i] - 'a' + 10;
    } else {
      return 0;
    }
  }
  return 1;
}
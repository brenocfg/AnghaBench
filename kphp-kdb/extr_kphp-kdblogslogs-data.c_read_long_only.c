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

int read_long_only (const char *s, long long *x) {
  int mul = 1;
  if (s[0] == '-' || s[0] == '+') {
    if (s[0] == '-') {
      mul = -1;
    }
    s++;
  }

  const char *num_start = s;
  unsigned long long val = 0;
  while ('0' <= *s && *s <= '9') {
    val = val * 10 + (*s++ - '0');
  }

  *x = val * mul;

  return s > num_start;
}
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

inline int strcmp_void (const void *x, const void *y) {
  const char *s1 = *(const char **)x;
  const char *s2 = *(const char **)y;
  while (*s1 == *s2 && *s1 != ' ')
    s1++, s2++;
  return *s1-*s2;
}
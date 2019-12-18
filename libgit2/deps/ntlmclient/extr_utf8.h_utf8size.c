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

size_t utf8size(const void *str) {
  const char *s = (const char *)str;
  size_t size = 0;
  while ('\0' != s[size]) {
    size++;
  }

  // we are including the null terminating byte in the size calculation
  size++;
  return size;
}
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

int utf8ncmp(const void *src1, const void *src2, size_t n) {
  const unsigned char *s1 = (const unsigned char *)src1;
  const unsigned char *s2 = (const unsigned char *)src2;

  while ((('\0' != *s1) || ('\0' != *s2)) && (0 != n--)) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }

    s1++;
    s2++;
  }

  // both utf8 strings matched
  return 0;
}
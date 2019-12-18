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
 int hex2int (int /*<<< orphan*/ ) ; 

int cb_sscan(char *to_buf, size_t *to_length, const char *buf) {
  if (!to_buf || !to_length || !buf) {
    return -1;
  }
  *to_length = 0;
  const char *f = buf;
  char *t = to_buf;
  while (*f) {
    for (; *f == ' '; f++) {
    }
    while (*f != ' ' && *f != '\n') {
      int h0 = (*f ? hex2int(*f++) : -1);
      int h1 = (*f ? hex2int(*f++) : -1);
      char ch = (*f ? *f++ : '\0');
      if (h0 < 0 || h1 < 0 || ch != ' ') {
        return -1;
      }
      *t++ = (h0 << 4) | h1;
      *to_length += 1;
    }
    if (*f == ' ') {
      while (*++f && *f != '\n') {
      }
    }
    if (*f && *f++ != '\n') {
      return -1;
    }
  }
  return 0;
}
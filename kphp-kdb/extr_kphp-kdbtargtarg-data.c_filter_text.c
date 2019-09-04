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

__attribute__((used)) static char *filter_text (char *to, const char *text, int len) {
  char *q = to, *end = to + len;
  while (q < end) {
    if ((unsigned char) *text < ' ' && *text != 9) {
      *q++ = ' ';
      text++;
    } else {
      *q++ = *text++;
    }
  }
  *q = 0;
  return to;
}
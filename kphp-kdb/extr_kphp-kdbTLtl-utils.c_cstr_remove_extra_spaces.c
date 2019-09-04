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

void cstr_remove_extra_spaces (char *buf) {
  char *s, *w, last;
  for (s = buf, w = buf, last = ' '; *s; s++) {
    if (*s == ' ' && last == ' ') {
      continue;
    }
    last = *w++ = *s;
  }
  /* remove trailing spaces */
  *w-- = 0;
  while (w >= buf && *w == ' ') {
    *w-- = 0;
  }
}
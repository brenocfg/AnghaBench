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

void split (char *s, char **f, int *fn, int limit) {
  int bal = 0;
  int cur = 0;
  int ins = 0;
#define add(s) if (cur < limit) {f[cur++] = s;} else {*fn = 0; return;}

  *fn = 0;
  add (s);
  while (*s) {
    if (*s == '\'') {
      ins ^= 1;
    } else if (*s == '(') {
      if (!ins) {
        bal++;
      }
    } else if (*s == ')') {
      if (!ins) {
        bal--;
      }
    } else if (*s == ',' && bal == 0 && !ins) {
      *s = 0;
      add (s + 1);
    }
    s++;
  }

  *fn = cur;
#undef add
}
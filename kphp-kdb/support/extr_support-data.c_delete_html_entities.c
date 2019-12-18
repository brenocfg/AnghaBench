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
 int /*<<< orphan*/  check (char*,int) ; 

void delete_html_entities (char *v) {
  int i;

  for (i = 0; v[i]; i++) {
    int ti = i;
    if (v[i + 1] == '#' && (v[i] == '&' || v[i] == '$')) {
      if (v[i + 2] != 'x') {
        for (i += 2; '0' <= v[i] && v[i] <= '9'; i++) {
        }
      } else {
        for (i += 3; ('0' <= v[i] && v[i] <= '9') || ('a' <= v[i] && v[i] <= 'f') || ('A' <= v[i] && v[i] <= 'F'); i++) {
        }
      }
      while (ti != i) {
        v[ti++] = ' ';
      }

      if (v[i] != ';') {
        i--;
      }
    } else if (v[i] == '%' && '0' <= v[i + 1] && v[i + 1] <= '7' &&
                            (('0' <= v[i + 2] && v[i + 2] <= '9') ||
                             ('a' <= v[i + 2] && v[i + 2] <= 'f') ||
                             ('A' <= v[i + 2] && v[i + 2] <= 'F'))) {
      i += 2;

      while (ti != i) {
        v[ti++] = ' ';
      }
    }
  }

#define check(s, l)                         \
  if (!strncmp (v + i + 2, s + 2, l - 2)) { \
    int end = i + l;                        \
    while (i < end) {                       \
      v[i++] = ' ';                         \
    }                                       \
    i--;                                    \
  }

  for (i = 0; v[i]; i++) {
    if (v[i] == '&' && v[i + 1] == '#') {
      check ("&#amp;", 6);
      check ("&#gt;", 5);
      check ("&#lt;", 5);
      check ("&#quot;", 7);
      check ("&#33;", 5);
      check ("&#34;", 5);
      check ("&#36;", 5);
      check ("&#39;", 5);
      check ("&#60;", 5);
      check ("&#62;", 5);
      check ("&#8232;", 7);
      check ("&#8233;", 7);
    }
  }

#undef check
}
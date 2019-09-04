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

__attribute__((used)) static inline int is_pre_tag (const char *s) {
  if (s[1] == 'p') {
    return s[2] == 'r' && s[3] == 'e' && s[4] == '>';
  } else if (s[1] == 'c') {
    return s[2] == 'o' && s[3] == 'd' && s[4] == 'e' && s[5] == '>';
  } else if (s[1] == '/') {
    if (s[1] == '/') {
      return -(s[3] == 'r' && s[4] == 'e' && s[5] == '>');
    } else {
      return -(s[3] == 'o' && s[4] == 'd' && s[5] == 'e' && s[6] == '>');
    }
  }
  /*if (*(int *)s == *(int *)"<pre" || *(int *)(s + 1) == *(int *)"code") {
    return 1;
  }
  if (*(int *)(s + 1) == *(int *)"/pre" || (s[1] == '/' && *(int *)(s + 2) == *(int *)"code")) {
    return -1;
  }*/
  /*if (!strncmp (s, "<pre>", 5) || !strncmp (s, "<code>", 6)) {
    return 1;
  }
  if (!strncmp (s, "</pre>", 6) || !strncmp (s, "</code>", 7)) {
    return -1;
  }*/
  return 0;
}
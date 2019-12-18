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
 int remove_diacritics (int) ; 

__attribute__((used)) static inline char next_character (const char *s, int *_i) {
  int i = *_i;
  char cur = s[i];
  if (cur == '&') {
    if (s[i + 1] == 'a' && s[i + 2] == 'm' && s[i + 3] == 'p' && s[i + 4] == ';') {
      i += 4;
    } else if (s[i + 1] == '#') {
      int r = 0, ti = i;
      for (i += 2; '0' <= s[i] && s[i] <= '9'; i++) {
        r = r * 10 + s[i] - '0';
      }
      if (s[i] == ';') {
        int c = remove_diacritics (r);
        if (c <= 255) {
          cur = c;
        } else {
          cur = 0;
        }
      } else {
        i = ti;
      }
    } else if (s[i + 1] == 'l' && s[i + 2] == 't' && s[i + 3] == ';') {
      i += 3, cur = '<';
    } else if (s[i + 1] == 'g' && s[i + 2] == 't' && s[i + 3] == ';') {
      i += 3, cur = '>';
    } else if (s[i + 1] == 'q' && s[i + 2] == 'u' && s[i + 3] == 'o' && s[i + 4] == 't' && s[i + 5] == ';') {
      i += 5, cur = '"';
    }
  } else if (cur == '<') {
    if (s[i + 1] == 'b' && s[i + 2] == 'r' && s[i + 3] == '>') {
      i += 3, cur = '\n';
    }
  }
  *_i = i;

  return cur;
}
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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND (char const) ; 
 scalar_t__ log10 (int) ; 
 size_t sprintf (char*,char*,int) ; 

size_t cb_sprint(char *to_buf, const char *buf, ssize_t length,
    ssize_t max_width, ssize_t max_lines) {
  if (length <= 0) {
    if (to_buf) {
      *to_buf = '\0';
    }
    return 0;
  }

  char *s = to_buf;
  size_t n = 0;

#define APPEND(v) if (s) { *s++ = (v); } n++

  size_t i = 0;
  size_t num_lines = 0;

  size_t chars_per_line;
  if (max_width >= 0) {
    chars_per_line = (max_width > 6 ? ((max_width - 2) >> 2) : 1);
  } else {
    size_t max_cpl = 1;
    size_t curr_cpl = 0;
    for (i = 0; i < length; i++) {
      unsigned char ch = buf[i++];
      curr_cpl++;
      if (ch == '\n') {
        if (curr_cpl > max_cpl) {
          max_cpl = curr_cpl;
        }
        if (max_lines >= 0 && ++num_lines > max_lines) {
          break;
        }
        curr_cpl = 0;
      }
    }
    chars_per_line = max_cpl;
  }

  i = 0;
  num_lines = 0;
  while (1) {
    size_t j;
    size_t rem = chars_per_line;
    for (j = i; j < length && rem; ) {
      unsigned char ch = buf[j++];
      static const char* hexchars = "0123456789ABCDEF";
      APPEND(' ');
      APPEND(hexchars[(ch >> 4) & 0xF]);
      APPEND(hexchars[ch & 0xF]);
      rem--;
      if (ch == '\n') {
        break;
      }
    }
    size_t rem2 = rem;
    for (rem2 = rem; rem2 > 0; rem2--) {
      APPEND(' ');
      APPEND(' ');
      APPEND(' ');
    }
    APPEND(' ');
    APPEND(' ');
    while (i < j) {
      unsigned char ch = buf[i++];
      APPEND(ch < 32 || ch > 126 ? '.' : ch);
    }
    if (i >= length) {
      break;
    }
    if (max_lines >= 0 && ++num_lines > max_lines) {
      for (rem2 = rem; rem2 > 0; rem2--) {
        APPEND(' ');
      }
      APPEND(' ');
      APPEND('+');
      if (s) {
        size_t k = sprintf(s, "%zd", length - i);
        s += k;
        n += k;
      } else {
        n += (int)(log10(length - i) + 0.5) + 1;
      }
      break;
    }
    APPEND('\n');
  }
  if (s) {
    *s++ = '\0';
  }
  return n;
}
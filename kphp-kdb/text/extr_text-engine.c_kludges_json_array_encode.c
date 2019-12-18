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
 int /*<<< orphan*/  assert (int) ; 
 int utf8_json_encode (char*,int,char*,int) ; 

int kludges_json_array_encode (char *to, int to_size, char *from, int from_size, int flags) {
  char *from_end = from + from_size, *to_end = to + to_size - 8, *to_start = to;
  int out_n = 0, len;

  if (to_size < 8 || from_size < 0) {
    return -1;
  }

  *to++ = '{';

  while (from < from_end && to < to_end) {
    if (*from != 1 && *from != 2) {
      break;
    }
    char *p = from, *q = 0;
    while (p < from_end && *p != '\t') {
      if (*p == ' ' && !q) {
	q = p;
      }
      p++;
    }
    if (!(flags & *from) || !q) {
      from = p + 1;
      continue;
    }
    *to++ = '"';
    len = utf8_json_encode (to, to_end - to, from + 1, q - from - 1);
    if (len < 0) {
      return len;
    }
    to += len;
    if (to > to_end) {
      return -1;
    }
    to[0] = '"';
    to[1] = ':';
    to[2] = '"';
    to += 3;
    len = utf8_json_encode (to, to_end - to, q + 1, p - q - 1);
    if (len < 0) {
      return len;
    }
    to += len;
    if (to > to_end) {
      return -1;
    }
    *to++ = '"';
    *to++ = ',';
    out_n++;
    from = p + 1;
  }

  if (out_n) {
    --to;
  }
  *to++ = '}';
  assert (to <= to_end + 8);
  return to - to_start;
}
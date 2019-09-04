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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char const*,int const) ; 

int get_http_header (const char *qHeaders, const int qHeadersLen, char *buffer, int b_len, const char *arg_name, const int arg_len) {
  const char *where = qHeaders;
  const char *where_end = where + qHeadersLen;
  while (where < where_end) {
    const char *start = where;
    while (where < where_end && (*where != ':' && *where != '\n')) {
      ++where;
    }
    if (where == where_end) {
      buffer[0] = 0;
      return -1;
    }
    if (*where == ':') {
      if (arg_len == where - start && !strncasecmp (arg_name, start, arg_len)) {
        where++;
        while (where < where_end && (*where == 9 || *where == 32)) {
          where++;
        }
        start = where;
        while (where < where_end && *where != '\r' && *where != '\n') {
          ++where;
        }
        while (where > start && (where[-1] == ' ' || where[-1] == 9)) {
          where--;
        }
        b_len--;
        if (where - start < b_len) {
          b_len = where - start;
        }
        memcpy (buffer, start, b_len);
        buffer[b_len] = 0;
        return b_len;
      }
      ++where;
    }
    while (where < where_end && *where != '\n') {
      ++where;
    }
    if (where < where_end) {
      ++where;
    }
  }
  buffer[0] = 0;
  return -1;
}
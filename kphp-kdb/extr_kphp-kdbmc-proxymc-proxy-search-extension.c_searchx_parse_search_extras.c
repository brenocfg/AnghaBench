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
 int MAX_RES ; 
 int Q_limit ; 
 char* Q_limit_end ; 
 char const* Q_limit_ptr ; 
 int Q_order ; 
 int Q_raw ; 
 int Q_searchx_hash_off ; 
 scalar_t__ Q_slice_limit ; 
 int /*<<< orphan*/  assert (int) ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static const char *searchx_parse_search_extras (const char *key) {
  const char *ptr = key;
  Q_raw = 0;
  Q_order = 0;
  Q_limit = 0;
  Q_slice_limit = 0;
  Q_limit_ptr = Q_limit_end = 0;

  ptr += 6;
  assert (*ptr == 'x' || *ptr == 'u');
  if (*ptr == 'u') {
    Q_order |= 2;
    ptr++;
    if ('a' <= *ptr && *ptr <= 'z') {
      ptr++;
    }
  } else {
    ptr++;
  }

  if (*ptr != '#' && *ptr != '%') {
    Q_limit = -1;
    return 0;
  }

  Q_searchx_hash_off = ptr - key;

  if (*ptr == '%') {
    Q_raw = 1;
  }
  ptr ++;
  Q_order |= 8;
  Q_order |= 4;

  while (*ptr && *ptr != '(' && *ptr != '<' && *ptr != '[') {
    ptr ++;
  }
  if (!*ptr) {
    Q_limit = -1;
    return ptr;
  }
  ptr --;
  while (*ptr >= '0' && *ptr <='9') {
    ptr --;
  }
  ptr ++;
  char *qtr;
  Q_limit = strtol (ptr, &qtr, 10);
  Q_limit_ptr = ptr;
  Q_limit_end = qtr;
  if (Q_limit > MAX_RES) { Q_limit = MAX_RES; }
  return qtr;
}
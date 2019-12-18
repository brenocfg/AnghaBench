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

__attribute__((used)) static unsigned long long extract_num (const char *key, int key_len, char **eptr) {
  const char *ptr = key, *ptr_e = key + key_len, *num_st;
  unsigned long long x;
  while (ptr < ptr_e && (*ptr < '0' || *ptr > '9')) {
    ptr++;
  }
  if (ptr == ptr_e) {
    if (eptr) {
      *eptr = (char *)ptr;
    }
    return (unsigned long long) -1;
  }
  do {
    num_st = ptr;
    x = 0;
    while (ptr < ptr_e && *ptr >= '0' && *ptr <= '9') {
      if (x >= 0x7fffffffffffffffLL / 10) {
        if (eptr) {
          *eptr = (char *)ptr;
        }
        return (unsigned long long) -1;
      }
      x = x*10 + (*ptr - '0');
      ptr++;
    }
    if (ptr == num_st) {
      if (eptr) {
        *eptr = (char *)ptr;
      }
      return (unsigned long long) -1;
    }
  } while (num_st == key && ptr < ptr_e && *ptr++ == '~');
  if (eptr) {
    *eptr = (char *)ptr;
  }
  return x;
}
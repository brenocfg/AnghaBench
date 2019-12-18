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
 scalar_t__ MAX_RES ; 
 scalar_t__ Q_limit ; 
 char const* Q_limit_end ; 
 char const* Q_limit_ptr ; 
 int Q_order ; 
 int Q_raw ; 
 scalar_t__ Q_slice_limit ; 
 scalar_t__ strtol (char const*,char**,int) ; 

__attribute__((used)) static const char *search_parse_search_extras (const char *ptr) {
  Q_raw = 0;
  Q_order = 0;
  Q_limit = 0;
  Q_slice_limit = 0;

  Q_limit_ptr = Q_limit_end = 0;

  if (*ptr != '#') {
    return ptr;
  }
  ptr++;
  while (*ptr != '(' && *ptr != '[') {
    if (*ptr == '%') {
      Q_raw = 1;
    } else if (*ptr == 'X') { 
    } else if (*ptr == 'i') {
    	Q_order &= ~4; 
    } else if (*ptr == 'I') {
    	Q_order |= 4;
    } else if (*ptr == 'P' || *ptr == 'T') {
      Q_order |= 8;
    } else if (*ptr == 'U') {
      Q_order |= 2;
    } else if (*ptr == 'V') {
      //nothing to do
    } else if ('A' <= *ptr && *ptr <= 'Z') {
      Q_order |= 4;
      Q_order |= 8;
    } else if (('a' <= *ptr && *ptr <= 'z') || *ptr == '?') {
      Q_order &= ~4;
      Q_order |= 8;
    } else if ('0' <= *ptr && *ptr <= '9') {
      Q_limit_ptr = ptr;
      char *qtr;
      Q_limit = strtol (ptr, &qtr, 10);
      ptr = qtr;
      Q_limit_end = ptr;
      if (Q_limit < 0) { Q_limit = 0; }
      if (Q_limit > MAX_RES) { Q_limit = MAX_RES; }
      ptr--;
    } else {
      return ptr;
    }
    ptr++;
  }
  return ptr;
}
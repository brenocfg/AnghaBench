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
 int CAT_FR_ALL ; 
 int CAT_FR_FR ; 
 size_t MAX_PRIVACY_LEN ; 
 int* P ; 
 size_t PL ; 
 int PL_M_ALLOW ; 
 int PL_M_CAT ; 
 int PL_M_DENY ; 
 int PL_M_MASK ; 
 int PL_M_USER ; 

__attribute__((used)) static int parse_privacy (const char *text, int len) {
  const char *end = text + len;
  int x, y;
  PL = 0;
  while (text < end) {
    switch (*text) {
    case '+':
      x = PL_M_USER | PL_M_ALLOW;
      break;
    case '*':
      x = PL_M_CAT | PL_M_ALLOW;
      break;
    case '-':
      x = PL_M_USER | PL_M_DENY;
      break;
    case '/':
      x = PL_M_CAT | PL_M_DENY;
      break;
    default:
      return -1;
    }
    if (++text >= end) {
      return -1;
    }
    if (*text > '9') {
      if (x & PL_M_CAT) {
        switch (*text) {
        case 'A':
          y = CAT_FR_ALL;
          break;
        case 'G':
          y = CAT_FR_FR;
          break;
        default:
          return -1;
        }
        text++;
      } else {
        return -1;
      }
    } else {
      if (*text < '0') {
        return -1;
      }
      y = 0;
      while (text < end && *text >= '0' && *text <= '9') {
        if (y > PL_M_MASK / 10) {
          return -1;
        }
        y = y * 10 + (*text++ - '0');
      }
      if (y > PL_M_MASK || ((x & PL_M_CAT) && y > 30)) {
        return -1;
      }
    }
    P[PL++] = x | y;  
    if (PL >= MAX_PRIVACY_LEN) {
      return -1;
    }
  }
  P[PL] = -1;
  return PL;
}
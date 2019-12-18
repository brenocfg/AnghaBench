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

char *t_skipspc (char *ptr, char *end) {
  while (1) {
    while (ptr < end && (*ptr == ' ' || *ptr == 9 || *ptr == 13 || *ptr == 10)) {
      ptr++;
    }
    if (ptr + 2 <= end && ptr[0] == '*' && ptr[1] == '/') {
      ptr += 2;
      continue;
    }
    if (ptr + 2 > end || ptr[0] != '/' || ptr[1] != '*') {
      break;
    }
    ptr += 2;
    if (ptr < end && (ptr[0] == '!' || ptr[0] == '?')) {
      ptr++;
      continue;
    }
    while (ptr + 2 <= end && (ptr[0] != '*' || ptr[1] != '/')) {
      ptr++;
    }
    if (ptr + 2 > end) {
      return end;
    }
    ptr += 2;
  }
  return ptr;
}
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

int parse_account_type (char *ptr, char **endptr) {
  int i, res = 0;

  for (i = 0; i < 3; i++) {
    if (*ptr < 'A' || *ptr > 'Z') {
      break;
    }
    res = res * 27 + (*ptr - 'A') + 1;
    ++ptr;
  }

  *endptr = ptr;
  return res;
}
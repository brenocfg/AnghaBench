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
 int INT_MAX ; 

inline void kwrite_print_int (char **s, const char *name, int name_len, int i) {
  if (i < 0) {
    i = INT_MAX;
  }

  *--*s = ' ';
  *--*s = ']';

  do {
    *--*s = i % 10 + '0';
    i /= 10;
  } while (i > 0);

  *--*s = ' ';

  while (--name_len >= 0) {
    *--*s = name[name_len];
  }

  *--*s = '[';
}
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

void del_spaces (char *s) {
  if (s != NULL) {
    char *r = s;
    int bal = 0;
    while (*s) {
      if (*s != ' ' || bal) {
        *r++ = *s;
      }
      if (*s == '[') {
        bal++;
      }
      if (*s == ']') {
        bal--;
      }
      s++;
    }
    *r = 0;
  }
}
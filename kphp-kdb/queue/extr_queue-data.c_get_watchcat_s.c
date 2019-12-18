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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

char *get_watchcat_s (unsigned long long h) {
  static char buf[100];
  char *s = buf;
  *s++ = 'w';
  *s++ = '_';
  while (h) {
    int x = h % 62;
    h /= 62;
    if (x < 26) {
      *s++ = x + 'A';
    } else {
      x -= 26;
      if (x < 26) {
        *s++ = x + 'a';
      } else {
        x -= 26;
        if (x < 10) {
          *s++ = x + '0';
        } else {
          assert (0);
        }
      }
    }
  }
  *s++ = 0;

  return buf;
}
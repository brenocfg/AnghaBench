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
 int /*<<< orphan*/  C (char,char) ; 
 int /*<<< orphan*/  likely (int) ; 

int write_str (char *d, int mx_len, char *s) {
  int tmp = mx_len;
  while (*s) {
#define C(x, y) case x: if (likely (--mx_len > 0)) *d++ = '\\'; if (likely (--mx_len > 0)) *d++ = y; break;
    switch (*s) {
      C('"', '"');
      C('\\', '\\');
      C('/', '/');
      C('\b', 'b');
      C('\f', 'f');
      C('\n', 'n');
      C('\r', 'r');
      C('\t', 't');
      default:
        if (likely (--mx_len > 0)) *d++ = *s;
    }
#undef C
    s++;
  }
  *d = 0;
  return  tmp - mx_len;
}
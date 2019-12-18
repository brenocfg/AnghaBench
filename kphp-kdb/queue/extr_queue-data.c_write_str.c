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
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

int write_str (char *d, char *s, int sn) {
  char *st = d;
  int i;
  for (i = 0; i < sn; i++) {
    char c = s[i];
#define C(x, y) case x: *d++ = '\\', *d++ = y; break;
    switch (c) {
      C('"', '"');
      C('\\', '\\');
      C('/', '/');
      C('\b', 'b');
      C('\f', 'f');
      C('\n', 'n');
      C('\r', 'r');
      C('\t', 't');
      default:
        if ((unsigned char)c >= 32) {
          *d++ = c;
        } else {
          //TODO its TOTALLY WRONG
          d += sprintf (d,"\\u%04x", c);
        }
    }
#undef C
  }
  return d - st;
}
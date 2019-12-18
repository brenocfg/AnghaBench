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
 int snprintf (char*,size_t,char*,char*,char const* const) ; 

void
Concatinate(char *buf, size_t sz, int argc, const char *const *argv)
{
  int i, n;
  unsigned pos;

  *buf = '\0';
  for (pos = i = 0; i < argc; i++) {
    n = snprintf(buf + pos, sz - pos, "%s%s", i ? " " : "", argv[i]);
    if (n < 0) {
      buf[pos] = '\0';
      break;
    }
    if ((pos += n) >= sz)
      break;
  }
}
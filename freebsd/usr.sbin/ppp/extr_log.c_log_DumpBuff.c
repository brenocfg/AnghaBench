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
typedef  char u_char ;

/* Variables and functions */
 scalar_t__ isprint (char const) ; 
 scalar_t__ log_IsKept (int) ; 
 int /*<<< orphan*/  log_Printf (int,char*,char const*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
log_DumpBuff(int lev, const char *hdr, const u_char *ptr, int n)
{
  if (log_IsKept(lev)) {
    char buf[68];
    char *b, *c;

    if (hdr && *hdr)
      log_Printf(lev, "%s\n", hdr);
    while (n > 0) {
      b = buf;
      c = b + 50;
      for (b = buf; b != buf + 48 && n--; b += 3, ptr++) {
	sprintf(b, " %02x", (int) *ptr);
        *c++ = isprint(*ptr) ? *ptr : '.';
      }
      memset(b, ' ', 50 - (b - buf));
      *c = '\0';
      log_Printf(lev, "%s\n", buf);
    }
  }
}
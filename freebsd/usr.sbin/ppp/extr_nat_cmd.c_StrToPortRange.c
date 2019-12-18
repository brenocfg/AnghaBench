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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int StrToPort (char const*,int /*<<< orphan*/ *,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
StrToPortRange(const char *str, u_short *low, u_short *high, const char *proto)
{
  char *minus;
  int res;

  minus = strchr(str, '-');
  if (minus)
    *minus = '\0';		/* Cheat the const-ness ! */

  res = StrToPort(str, low, proto);

  if (minus)
    *minus = '-';		/* Cheat the const-ness ! */

  if (res == 0) {
    if (minus)
      res = StrToPort(minus + 1, high, proto);
    else
      *high = *low;
  }

  return res;
}
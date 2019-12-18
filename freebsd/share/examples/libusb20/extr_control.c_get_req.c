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
 int /*<<< orphan*/ * reqnames ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int strtoul (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_req(const char *reqname)
{
  size_t i;
  size_t l = strlen(reqname);

  for (i = 0;
       i < sizeof reqnames / sizeof reqnames[0];
       i++)
    if (strncasecmp(reqname, reqnames[i], l) == 0)
      return i;

  return strtoul(reqname, 0, 0);
}
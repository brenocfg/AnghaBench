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
 int svn_ctype_casecmp (int const,int const) ; 

int
svn_cstring_casecmp(const char *str1, const char *str2)
{
  for (;;)
    {
      const int a = *str1++;
      const int b = *str2++;
      const int cmp = svn_ctype_casecmp(a, b);
      if (cmp || !a || !b)
        return cmp;
    }
}
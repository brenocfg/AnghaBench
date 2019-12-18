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
typedef  char wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  wcslen (char const*) ; 

__attribute__((used)) static unsigned FindExt(const wchar_t *s, unsigned *extLen)
{
  unsigned len = (unsigned)wcslen(s);
  unsigned i;
  for (i = len; i > 0; i--)
  {
    if (s[i - 1] == '.')
    {
      *extLen = len - i;
      return i - 1;
    }
  }
  *extLen = 0;
  return len;
}
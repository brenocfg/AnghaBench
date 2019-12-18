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
typedef  unsigned int wchar_t ;
typedef  unsigned int Byte ;

/* Variables and functions */
 unsigned int const MAKE_CHAR_UPPER (unsigned int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static unsigned FindItem(const char * const *items, unsigned num, const wchar_t *s, unsigned len)
{
  unsigned i;
  for (i = 0; i < num; i++)
  {
    const char *item = items[i];
    unsigned itemLen = (unsigned)strlen(item);
    unsigned j;
    if (len != itemLen)
      continue;
    for (j = 0; j < len; j++)
    {
      unsigned c = (Byte)item[j];
      if (c != s[j] && MAKE_CHAR_UPPER(c) != s[j])
        break;
    }
    if (j == len)
      return i;
  }
  return i;
}
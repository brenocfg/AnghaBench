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
 char* parsed_string (char*,char**,int) ; 
 char* strpbrk (char*,char const*) ; 

__attribute__((used)) static char *
parse_string (char **str, const char *delims, int cnt)
{
  int idx = 0;
  char *pch = *str, *p = NULL;
  char end;

  if ((*delims != 0x0) && (p = strpbrk (*str, delims)) == NULL)
    return NULL;

  end = !*delims ? 0x0 : *p;
  do {
    /* match number of delims */
    if (*pch == end)
      idx++;
    /* delim found, parse string then */
    if ((*pch == end && cnt == idx) || *pch == '\0')
      return parsed_string (pch, str, 1);
    /* advance to the first unescaped delim */
    if (*pch == '\\')
      pch++;
  } while (*pch++);

  return NULL;
}
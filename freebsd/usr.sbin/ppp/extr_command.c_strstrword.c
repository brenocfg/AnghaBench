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
 scalar_t__ isinword (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static char *
strstrword(char *big, const char *little)
{
  /* Get the first occurrence of the word ``little'' in ``big'' */
  char *pos;
  int len;

  pos = big;
  len = strlen(little);

  while ((pos = strstr(pos, little)) != NULL)
    if ((pos != big && isinword(pos[-1])) || isinword(pos[len]))
      pos++;
    else if (pos != big && pos[-1] == '\\')
      memmove(pos - 1, pos, strlen(pos) + 1);
    else
      break;

  return pos;
}
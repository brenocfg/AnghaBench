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
 size_t strlen (char*) ; 

__attribute__((used)) static void
unquote_string(char **pstr)
{
  char *str = *pstr;
  size_t i = strlen(str);

  if (i > 0 && ((*str == '"' && str[i - 1] == '"') ||
                (*str == '\'' && str[i - 1] == '\'')))
    {
      str[i - 1] = '\0';
      str++;
    }
  *pstr = str;
}
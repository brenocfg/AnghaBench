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
 scalar_t__ svn_ctype_isspace (char) ; 

__attribute__((used)) static void
trim_string(char **pstr)
{
  char *str = *pstr;
  size_t i;

  while (svn_ctype_isspace(*str))
    str++;
  *pstr = str;
  i = strlen(str);
  while ((i > 0) && svn_ctype_isspace(str[i-1]))
    i--;
  str[i] = '\0';
}
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
 scalar_t__ isspace (char const) ; 

int
strcmp_iw_ordered (const char *string1, const char *string2)
{
  while ((*string1 != '\0') && (*string2 != '\0'))
    {
      while (isspace (*string1))
	{
	  string1++;
	}
      while (isspace (*string2))
	{
	  string2++;
	}
      if (*string1 != *string2)
	{
	  break;
	}
      if (*string1 != '\0')
	{
	  string1++;
	  string2++;
	}
    }

  switch (*string1)
    {
      /* Characters are non-equal unless they're both '\0'; we want to
	 make sure we get the comparison right according to our
	 comparison in the cases where one of them is '\0' or '('.  */
    case '\0':
      if (*string2 == '\0')
	return 0;
      else
	return -1;
    case '(':
      if (*string2 == '\0')
	return 1;
      else
	return -1;
    default:
      if (*string2 == '(')
	return 1;
      else
	return *string1 - *string2;
    }
}
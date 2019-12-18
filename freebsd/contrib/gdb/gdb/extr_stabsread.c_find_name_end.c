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
 int /*<<< orphan*/  error (char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *
find_name_end (char *name)
{
  char *s = name;
  if (s[0] == '-' || *s == '+')
    {
      /* Must be an ObjC method symbol.  */
      if (s[1] != '[')
	{
	  error ("invalid symbol name \"%s\"", name);
	}
      s = strchr (s, ']');
      if (s == NULL)
	{
	  error ("invalid symbol name \"%s\"", name);
	}
      return strchr (s, ':');
    }
  else
    {
      return strchr (s, ':');
    }
}
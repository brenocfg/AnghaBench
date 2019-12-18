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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 char* strchr (char*,char) ; 
 unsigned int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,unsigned int) ; 
 char* type_name_no_tag (struct type const*) ; 

int
destructor_name_p (const char *name, const struct type *type)
{
  /* destructors are a special case.  */

  if (name[0] == '~')
    {
      char *dname = type_name_no_tag (type);
      char *cp = strchr (dname, '<');
      unsigned int len;

      /* Do not compare the template part for template classes.  */
      if (cp == NULL)
	len = strlen (dname);
      else
	len = cp - dname;
      if (strlen (name + 1) != len || strncmp (dname, name + 1, len) != 0)
	error ("name of destructor must equal name of class");
      else
	return 1;
    }
  return 0;
}
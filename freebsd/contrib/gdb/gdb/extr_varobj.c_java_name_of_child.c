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
struct varobj {int dummy; } ;

/* Variables and functions */
 char* cplus_name_of_child (struct varobj*,int) ; 

__attribute__((used)) static char *
java_name_of_child (struct varobj *parent, int index)
{
  char *name, *p;

  name = cplus_name_of_child (parent, index);
  /* Escape any periods in the name... */
  p = name;

  while (*p != '\000')
    {
      if (*p == '.')
	*p = '-';
      p++;
    }

  return name;
}
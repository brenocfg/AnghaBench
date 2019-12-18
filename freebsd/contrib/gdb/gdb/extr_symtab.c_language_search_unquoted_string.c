#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ la_language; } ;

/* Variables and functions */
 TYPE_1__* current_language ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ language_objc ; 

__attribute__((used)) static char *
language_search_unquoted_string (char *text, char *p)
{
  for (; p > text; --p)
    {
      if (isalnum (p[-1]) || p[-1] == '_' || p[-1] == '\0')
	continue;
      else
	{
	  if ((current_language->la_language == language_objc))
	    {
	      if (p[-1] == ':')     /* might be part of a method name */
		continue;
	      else if (p[-1] == '[' && (p[-2] == '-' || p[-2] == '+'))
		p -= 2;             /* beginning of a method name */
	      else if (p[-1] == ' ' || p[-1] == '(' || p[-1] == ')')
		{                   /* might be part of a method name */
		  char *t = p;

		  /* Seeing a ' ' or a '(' is not conclusive evidence
		     that we are in the middle of a method name.  However,
		     finding "-[" or "+[" should be pretty un-ambiguous.
		     Unfortunately we have to find it now to decide.  */

		  while (t > text)
		    if (isalnum (t[-1]) || t[-1] == '_' ||
			t[-1] == ' '    || t[-1] == ':' ||
			t[-1] == '('    || t[-1] == ')')
		      --t;
		    else
		      break;

		  if (t[-1] == '[' && (t[-2] == '-' || t[-2] == '+'))
		    p = t - 2;      /* method name detected */
		  /* else we leave with p unchanged */
		}
	    }
	  break;
	}
    }
  return p;
}
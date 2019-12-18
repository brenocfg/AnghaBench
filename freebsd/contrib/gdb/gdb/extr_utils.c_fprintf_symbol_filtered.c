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
struct ui_file {int dummy; } ;
typedef  enum language { ____Placeholder_language } language ;

/* Variables and functions */
 int /*<<< orphan*/  demangle ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  language_def (int) ; 
 char* language_demangle (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
fprintf_symbol_filtered (struct ui_file *stream, char *name,
			 enum language lang, int arg_mode)
{
  char *demangled;

  if (name != NULL)
    {
      /* If user wants to see raw output, no problem.  */
      if (!demangle)
	{
	  fputs_filtered (name, stream);
	}
      else
	{
	  demangled = language_demangle (language_def (lang), name, arg_mode);
	  fputs_filtered (demangled ? demangled : name, stream);
	  if (demangled != NULL)
	    {
	      xfree (demangled);
	    }
	}
    }
}
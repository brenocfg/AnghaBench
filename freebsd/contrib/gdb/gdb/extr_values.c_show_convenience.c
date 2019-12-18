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
struct internalvar {int /*<<< orphan*/  value; int /*<<< orphan*/  name; struct internalvar* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Val_pretty_default ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct internalvar* internalvars ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int /*<<< orphan*/  value_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_convenience (char *ignore, int from_tty)
{
  struct internalvar *var;
  int varseen = 0;

  for (var = internalvars; var; var = var->next)
    {
      if (!varseen)
	{
	  varseen = 1;
	}
      printf_filtered ("$%s = ", var->name);
      value_print (var->value, gdb_stdout, 0, Val_pretty_default);
      printf_filtered ("\n");
    }
  if (!varseen)
    printf_unfiltered ("No debugger convenience variables now defined.\n\
Convenience variables have names starting with \"$\";\n\
use \"set\" as in \"set $foo = 5\" to define them.\n");
}
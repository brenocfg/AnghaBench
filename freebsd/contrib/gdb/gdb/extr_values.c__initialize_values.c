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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  show_convenience ; 
 int /*<<< orphan*/  show_values ; 
 int /*<<< orphan*/  showlist ; 

void
_initialize_values (void)
{
  add_cmd ("convenience", no_class, show_convenience,
	   "Debugger convenience (\"$foo\") variables.\n\
These variables are created when you assign them values;\n\
thus, \"print $foo=1\" gives \"$foo\" the value 1.  Values may be any type.\n\n\
A few convenience variables are given values automatically:\n\
\"$_\"holds the last address examined with \"x\" or \"info lines\",\n\
\"$__\" holds the contents of the last address examined with \"x\".",
	   &showlist);

  add_cmd ("values", no_class, show_values,
	   "Elements of value history around item number IDX (or last ten).",
	   &showlist);
}
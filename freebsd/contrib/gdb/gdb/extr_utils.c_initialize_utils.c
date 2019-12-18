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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asm_demangle ; 
 char chars_per_line ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  demangle ; 
 int /*<<< orphan*/  init_page_info () ; 
 char lines_per_page ; 
 int /*<<< orphan*/  pagination_enabled ; 
 int /*<<< orphan*/  pagination_off_command ; 
 int /*<<< orphan*/  pagination_on_command ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_height_command ; 
 int /*<<< orphan*/  set_width_command ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  setprintlist ; 
 int /*<<< orphan*/  sevenbit_strings ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  showprintlist ; 
 int /*<<< orphan*/  var_boolean ; 
 int /*<<< orphan*/  var_uinteger ; 
 scalar_t__ xdb_commands ; 

void
initialize_utils (void)
{
  struct cmd_list_element *c;

  c = add_set_cmd ("width", class_support, var_uinteger, &chars_per_line,
		   "Set number of characters gdb thinks are in a line.",
		   &setlist);
  add_show_from_set (c, &showlist);
  set_cmd_sfunc (c, set_width_command);

  c = add_set_cmd ("height", class_support, var_uinteger, &lines_per_page,
		   "Set number of lines gdb thinks are in a page.", &setlist);
  add_show_from_set (c, &showlist);
  set_cmd_sfunc (c, set_height_command);

  init_page_info ();

  add_show_from_set
    (add_set_cmd ("demangle", class_support, var_boolean,
		  (char *) &demangle,
		  "Set demangling of encoded C++/ObjC names when displaying symbols.",
		  &setprintlist), &showprintlist);

  add_show_from_set
    (add_set_cmd ("pagination", class_support,
		  var_boolean, (char *) &pagination_enabled,
		  "Set state of pagination.", &setlist), &showlist);

  if (xdb_commands)
    {
      add_com ("am", class_support, pagination_on_command,
	       "Enable pagination");
      add_com ("sm", class_support, pagination_off_command,
	       "Disable pagination");
    }

  add_show_from_set
    (add_set_cmd ("sevenbit-strings", class_support, var_boolean,
		  (char *) &sevenbit_strings,
		  "Set printing of 8-bit characters in strings as \\nnn.",
		  &setprintlist), &showprintlist);

  add_show_from_set
    (add_set_cmd ("asm-demangle", class_support, var_boolean,
		  (char *) &asm_demangle,
		  "Set demangling of C++/ObjC names in disassembly listings.",
		  &setprintlist), &showprintlist);
}
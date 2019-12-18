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
 scalar_t__ PRINT_MAX_DEFAULT ; 
 int /*<<< orphan*/  add_alias_cmd (char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int addressprint ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  input_radix ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  output_radix ; 
 scalar_t__ prettyprint_arrays ; 
 scalar_t__ prettyprint_structs ; 
 scalar_t__ print_max ; 
 int /*<<< orphan*/  repeat_count_threshold ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_input_radix ; 
 int /*<<< orphan*/  set_output_radix ; 
 int /*<<< orphan*/  set_print ; 
 int /*<<< orphan*/  set_radix ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  setprintlist ; 
 int /*<<< orphan*/  show_print ; 
 int /*<<< orphan*/  show_radix ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  showprintlist ; 
 int /*<<< orphan*/  stop_print_at_null ; 
 int unionprint ; 
 int /*<<< orphan*/  var_boolean ; 
 int /*<<< orphan*/  var_uinteger ; 

void
_initialize_valprint (void)
{
  struct cmd_list_element *c;

  add_prefix_cmd ("print", no_class, set_print,
		  "Generic command for setting how things print.",
		  &setprintlist, "set print ", 0, &setlist);
  add_alias_cmd ("p", "print", no_class, 1, &setlist);
  /* prefer set print to set prompt */
  add_alias_cmd ("pr", "print", no_class, 1, &setlist);

  add_prefix_cmd ("print", no_class, show_print,
		  "Generic command for showing print settings.",
		  &showprintlist, "show print ", 0, &showlist);
  add_alias_cmd ("p", "print", no_class, 1, &showlist);
  add_alias_cmd ("pr", "print", no_class, 1, &showlist);

  add_show_from_set
    (add_set_cmd ("elements", no_class, var_uinteger, (char *) &print_max,
		  "Set limit on string chars or array elements to print.\n\
\"set print elements 0\" causes there to be no limit.",
		  &setprintlist),
     &showprintlist);

  add_show_from_set
    (add_set_cmd ("null-stop", no_class, var_boolean,
		  (char *) &stop_print_at_null,
		  "Set printing of char arrays to stop at first null char.",
		  &setprintlist),
     &showprintlist);

  add_show_from_set
    (add_set_cmd ("repeats", no_class, var_uinteger,
		  (char *) &repeat_count_threshold,
		  "Set threshold for repeated print elements.\n\
\"set print repeats 0\" causes all elements to be individually printed.",
		  &setprintlist),
     &showprintlist);

  add_show_from_set
    (add_set_cmd ("pretty", class_support, var_boolean,
		  (char *) &prettyprint_structs,
		  "Set prettyprinting of structures.",
		  &setprintlist),
     &showprintlist);

  add_show_from_set
    (add_set_cmd ("union", class_support, var_boolean, (char *) &unionprint,
		  "Set printing of unions interior to structures.",
		  &setprintlist),
     &showprintlist);

  add_show_from_set
    (add_set_cmd ("array", class_support, var_boolean,
		  (char *) &prettyprint_arrays,
		  "Set prettyprinting of arrays.",
		  &setprintlist),
     &showprintlist);

  add_show_from_set
    (add_set_cmd ("address", class_support, var_boolean, (char *) &addressprint,
		  "Set printing of addresses.",
		  &setprintlist),
     &showprintlist);

  c = add_set_cmd ("input-radix", class_support, var_uinteger,
		   (char *) &input_radix,
		   "Set default input radix for entering numbers.",
		   &setlist);
  add_show_from_set (c, &showlist);
  set_cmd_sfunc (c, set_input_radix);

  c = add_set_cmd ("output-radix", class_support, var_uinteger,
		   (char *) &output_radix,
		   "Set default output radix for printing of values.",
		   &setlist);
  add_show_from_set (c, &showlist);
  set_cmd_sfunc (c, set_output_radix);

  /* The "set radix" and "show radix" commands are special in that they are
     like normal set and show commands but allow two normally independent
     variables to be either set or shown with a single command.  So the
     usual add_set_cmd() and add_show_from_set() commands aren't really
     appropriate. */
  add_cmd ("radix", class_support, set_radix,
	   "Set default input and output number radices.\n\
Use 'set input-radix' or 'set output-radix' to independently set each.\n\
Without an argument, sets both radices back to the default value of 10.",
	   &setlist);
  add_cmd ("radix", class_support, show_radix,
	   "Show the default input and output number radices.\n\
Use 'show input-radix' or 'show output-radix' to independently show each.",
	   &showlist);

  /* Give people the defaults which they are used to.  */
  prettyprint_structs = 0;
  prettyprint_arrays = 0;
  unionprint = 1;
  addressprint = 1;
  print_max = PRINT_MAX_DEFAULT;
}
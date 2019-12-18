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
struct symtab_and_line {TYPE_1__* symtab; int /*<<< orphan*/  line; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;
struct TYPE_2__ {int /*<<< orphan*/ * fullname; int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  error (char*) ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 int /*<<< orphan*/  mi_valid_noargs (char*,int,char**) ; 
 int /*<<< orphan*/  set_default_source_symtab_and_line () ; 
 int /*<<< orphan*/  symtab_to_filename (TYPE_1__*) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiout ; 

enum mi_cmd_result
mi_cmd_file_list_exec_source_file(char *command, char **argv, int argc)
{
  struct symtab_and_line st;
  int optind = 0;
  char *optarg;
  
  if ( !mi_valid_noargs("mi_cmd_file_list_exec_source_file", argc, argv) )
    error ("mi_cmd_file_list_exec_source_file: Usage: No args");

  
  /* Set the default file and line, also get them */
  set_default_source_symtab_and_line();
  st = get_current_source_symtab_and_line();

  /* We should always get a symtab. 
     Apparently, filename does not need to be tested for NULL.
     The documentation in symtab.h suggests it will always be correct */
  if (!st.symtab)
    error ("mi_cmd_file_list_exec_source_file: No symtab");

  /* Extract the fullname if it is not known yet */
  if (st.symtab->fullname == NULL)
    symtab_to_filename (st.symtab);

  /* We may not be able to open the file (not available). */
  if (st.symtab->fullname == NULL)
    error ("mi_cmd_file_list_exec_source_file: File not found");

  /* Print to the user the line, filename and fullname */
  ui_out_field_int (uiout, "line", st.line);
  ui_out_field_string (uiout, "file", st.symtab->filename);
  ui_out_field_string (uiout, "fullname", st.symtab->fullname);

  return MI_CMD_DONE;
}
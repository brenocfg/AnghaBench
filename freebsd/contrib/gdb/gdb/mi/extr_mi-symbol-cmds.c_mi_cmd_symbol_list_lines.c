#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symtab {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;
struct TYPE_4__ {int nitems; TYPE_1__* item; } ;
struct TYPE_3__ {int /*<<< orphan*/  line; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 TYPE_2__* LINETABLE (struct symtab*) ; 
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct symtab* lookup_symtab (char*) ; 
 struct cleanup* make_cleanup_ui_out_list_begin_end (int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_out_field_core_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 

enum mi_cmd_result
mi_cmd_symbol_list_lines (char *command, char **argv, int argc)
{
  char *filename;
  struct symtab *s;
  int i;
  struct cleanup *cleanup_stack, *cleanup_tuple;

  if (argc != 1)
    error ("mi_cmd_symbol_list_lines: Usage: SOURCE_FILENAME");

  filename = argv[0];
  s = lookup_symtab (filename);

  if (s == NULL)
    error ("mi_cmd_symbol_list_lines: Unknown source file name.");

  /* Now, dump the associated line table.  The pc addresses are already
     sorted by increasing values in the symbol table, so no need to
     perform any other sorting. */

  cleanup_stack = make_cleanup_ui_out_list_begin_end (uiout, "lines");

  if (LINETABLE (s) != NULL && LINETABLE (s)->nitems > 0)
    for (i = 0; i < LINETABLE (s)->nitems; i++)
    {
      cleanup_tuple = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
      ui_out_field_core_addr (uiout, "pc", LINETABLE (s)->item[i].pc);
      ui_out_field_int (uiout, "line", LINETABLE (s)->item[i].line);
      do_cleanups (cleanup_tuple);
    }

  do_cleanups (cleanup_stack);

  return MI_CMD_DONE;
}
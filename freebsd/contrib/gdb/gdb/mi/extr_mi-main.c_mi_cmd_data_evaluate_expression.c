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
struct value {int dummy; } ;
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int MI_CMD_ERROR ; 
 int /*<<< orphan*/  VALUE_ADDRESS (struct value*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_EMBEDDED_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct value* evaluate_expression (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 int /*<<< orphan*/  mi_error_message ; 
 struct expression* parse_expression (char*) ; 
 int /*<<< orphan*/  ui_out_field_stream (int /*<<< orphan*/ ,char*,struct ui_stream*) ; 
 int /*<<< orphan*/  ui_out_stream_delete (struct ui_stream*) ; 
 struct ui_stream* ui_out_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  val_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*) ; 

enum mi_cmd_result
mi_cmd_data_evaluate_expression (char *command, char **argv, int argc)
{
  struct expression *expr;
  struct cleanup *old_chain = NULL;
  struct value *val;
  struct ui_stream *stb = NULL;

  stb = ui_out_stream_new (uiout);

  if (argc != 1)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_evaluate_expression: Usage: -data-evaluate-expression expression");
      return MI_CMD_ERROR;
    }

  expr = parse_expression (argv[0]);

  old_chain = make_cleanup (free_current_contents, &expr);

  val = evaluate_expression (expr);

  /* Print the result of the expression evaluation. */
  val_print (VALUE_TYPE (val), VALUE_CONTENTS (val),
	     VALUE_EMBEDDED_OFFSET (val), VALUE_ADDRESS (val),
	     stb->stream, 0, 0, 0, 0);

  ui_out_field_stream (uiout, "value", stb);
  ui_out_stream_delete (stb);

  do_cleanups (old_chain);

  return MI_CMD_DONE;
}
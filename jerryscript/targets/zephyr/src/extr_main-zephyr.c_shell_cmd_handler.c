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
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 int /*<<< orphan*/  jerry_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_value_from_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_function ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int shell_cmd_handler (char *source_buffer)
{
  jerry_value_t ret_val;

  ret_val = jerry_eval ((jerry_char_t *) source_buffer,
    strlen (source_buffer),
    JERRY_PARSE_NO_OPTS);

  if (jerry_value_is_error (ret_val))
  {
    /* User-friendly error messages require at least "cp" JerryScript
       profile. Include a message prefix in case "cp_minimal" profile
       is used. */
    printf ("Error executing statement: ");
    /* Clear error flag, otherwise print call below won't produce any
       output. */
    ret_val = jerry_get_value_from_error (ret_val, true);
  }

  if (!jerry_value_is_error (print_function))
  {
    jerry_value_t ret_val_print = jerry_call_function (print_function,
      jerry_create_undefined (),
      &ret_val,
      1);
    jerry_release_value (ret_val_print);
  }

  jerry_release_value (ret_val);

  return 0;
}
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
typedef  int /*<<< orphan*/  script ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  char jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 int JERRY_STANDALONE_EXIT_CODE_FAIL ; 
 int JERRY_STANDALONE_EXIT_CODE_OK ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_run (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_handler_print ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  register_js_function (char*,int /*<<< orphan*/ ) ; 

int test_jerry (int argc, char **argv)
{
  /* Suppress compiler errors */
  (void) argc;
  (void) argv;

  jerry_value_t ret_value = jerry_create_undefined ();

  const jerry_char_t script[] = "print ('Hello, World!');";
  printf ("This test run the following script code: [%s]\n\n", script);

  /* Initialize engine */
  jerry_init (JERRY_INIT_EMPTY);

  /* Register the print function in the global object. */
  register_js_function ("print", jerryx_handler_print);

  /* Setup Global scope code */
  ret_value = jerry_parse (NULL, 0, script, sizeof (script) - 1, JERRY_PARSE_NO_OPTS);

  if (!jerry_value_is_error (ret_value))
  {
    /* Execute the parsed source code in the Global scope */
    ret_value = jerry_run (ret_value);
  }

  int ret_code = JERRY_STANDALONE_EXIT_CODE_OK;

  if (jerry_value_is_error (ret_value))
  {
    printf ("Script Error!");

    ret_code = JERRY_STANDALONE_EXIT_CODE_FAIL;
  }

  jerry_release_value (ret_value);

  /* Cleanup engine */
  jerry_cleanup ();

  return ret_code;

}
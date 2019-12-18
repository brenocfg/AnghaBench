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
 int /*<<< orphan*/  JERRY_ERROR_COMMON ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  JERRY_LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 int JERRY_STANDALONE_EXIT_CODE_FAIL ; 
 int JERRY_STANDALONE_EXIT_CODE_OK ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_port_get_current_time () ; 
 int /*<<< orphan*/  jerry_port_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_run (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_help (char*) ; 
 int /*<<< orphan*/ * read_file (char const*,size_t*) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
main (int argc,
      char **argv)
{
  srand ((unsigned) jerry_port_get_current_time ());
  if (argc <= 1 || (argc == 2 && (!strcmp ("-h", argv[1]) || !strcmp ("--help", argv[1]))))
  {
    print_help (argv[0]);
    return JERRY_STANDALONE_EXIT_CODE_OK;
  }

  jerry_init (JERRY_INIT_EMPTY);
  jerry_value_t ret_value = jerry_create_undefined ();

  for (int i = 1; i < argc; i++)
  {
    const char *file_name = argv[i];
    size_t source_size;

    const jerry_char_t *source_p = read_file (file_name, &source_size);

    if (source_p == NULL)
    {
      ret_value = jerry_create_error (JERRY_ERROR_COMMON, (jerry_char_t *) "");
      break;
    }
    else
    {
      ret_value = jerry_parse (NULL, 0, source_p, source_size, JERRY_PARSE_NO_OPTS);

      if (!jerry_value_is_error (ret_value))
      {
        jerry_value_t func_val = ret_value;
        ret_value = jerry_run (func_val);
        jerry_release_value (func_val);
      }
    }

    if (jerry_value_is_error (ret_value))
    {
      break;
    }

    jerry_release_value (ret_value);
    ret_value = jerry_create_undefined ();
  }

  int ret_code = JERRY_STANDALONE_EXIT_CODE_OK;

  if (jerry_value_is_error (ret_value))
  {
    jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Unhandled exception: Script Error!\n");
    ret_code = JERRY_STANDALONE_EXIT_CODE_FAIL;
  }

  jerry_release_value (ret_value);
  jerry_cleanup ();

  return ret_code;
}
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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int jerry_size_t ;
typedef  char jerry_char_t ;

/* Variables and functions */
 scalar_t__ JERRY_ERROR_SYNTAX ; 
 int /*<<< orphan*/  JERRY_FEATURE_ERROR_MESSAGES ; 
 int /*<<< orphan*/  JERRY_LOG_LEVEL_ERROR ; 
 unsigned int SYNTAX_ERROR_CONTEXT_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 char* buffer ; 
 int /*<<< orphan*/  jerry_create_string (char const*) ; 
 int jerry_get_array_length (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_get_error_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_property_by_index (int /*<<< orphan*/ ,int) ; 
 int jerry_get_utf8_string_size (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_is_feature_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_port_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_string_to_utf8_char_buffer (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ jerry_value_is_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_object (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_file (char*,size_t*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static void
print_unhandled_exception (jerry_value_t error_value) /**< error value */
{
  assert (!jerry_value_is_error (error_value));

  jerry_char_t err_str_buf[256];

  if (jerry_value_is_object (error_value))
  {
    jerry_value_t stack_str = jerry_create_string ((const jerry_char_t *) "stack");
    jerry_value_t backtrace_val = jerry_get_property (error_value, stack_str);
    jerry_release_value (stack_str);

    if (!jerry_value_is_error (backtrace_val)
        && jerry_value_is_array (backtrace_val))
    {
      printf ("Exception backtrace:\n");

      uint32_t length = jerry_get_array_length (backtrace_val);

      /* This length should be enough. */
      if (length > 32)
      {
        length = 32;
      }

      for (uint32_t i = 0; i < length; i++)
      {
        jerry_value_t item_val = jerry_get_property_by_index (backtrace_val, i);

        if (!jerry_value_is_error (item_val)
            && jerry_value_is_string (item_val))
        {
          jerry_size_t str_size = jerry_get_utf8_string_size (item_val);

          if (str_size >= 256)
          {
            printf ("%3u: [Backtrace string too long]\n", i);
          }
          else
          {
            jerry_size_t string_end = jerry_string_to_utf8_char_buffer (item_val, err_str_buf, str_size);
            assert (string_end == str_size);
            err_str_buf[string_end] = 0;

            printf ("%3u: %s\n", i, err_str_buf);
          }
        }

        jerry_release_value (item_val);
      }
    }
    jerry_release_value (backtrace_val);
  }

  jerry_value_t err_str_val = jerry_value_to_string (error_value);
  jerry_size_t err_str_size = jerry_get_utf8_string_size (err_str_val);

  if (err_str_size >= 256)
  {
    const char msg[] = "[Error message too long]";
    err_str_size = sizeof (msg) / sizeof (char) - 1;
    memcpy (err_str_buf, msg, err_str_size + 1);
  }
  else
  {
    jerry_size_t string_end = jerry_string_to_utf8_char_buffer (err_str_val, err_str_buf, err_str_size);
    assert (string_end == err_str_size);
    err_str_buf[string_end] = 0;

    if (jerry_is_feature_enabled (JERRY_FEATURE_ERROR_MESSAGES)
        && jerry_get_error_type (error_value) == JERRY_ERROR_SYNTAX)
    {
      jerry_char_t *string_end_p = err_str_buf + string_end;
      unsigned int err_line = 0;
      unsigned int err_col = 0;
      char *path_str_p = NULL;
      char *path_str_end_p = NULL;

      /* 1. parse column and line information */
      for (jerry_char_t *current_p = err_str_buf; current_p < string_end_p; current_p++)
      {
        if (*current_p == '[')
        {
          current_p++;

          if (*current_p == '<')
          {
            break;
          }

          path_str_p = (char *) current_p;
          while (current_p < string_end_p && *current_p != ':')
          {
            current_p++;
          }

          path_str_end_p = (char *) current_p++;

          err_line = (unsigned int) strtol ((char *) current_p, (char **) &current_p, 10);

          current_p++;

          err_col = (unsigned int) strtol ((char *) current_p, NULL, 10);
          break;
        }
      } /* for */

      if (err_line != 0 && err_col != 0)
      {
        unsigned int curr_line = 1;

        bool is_printing_context = false;
        unsigned int pos = 0;

        size_t source_size;

        /* Temporarily modify the error message, so we can use the path. */
        *path_str_end_p = '\0';

        read_file (path_str_p, &source_size);

        /* Revert the error message. */
        *path_str_end_p = ':';

        /* 2. seek and print */
        while ((pos < source_size) && (buffer[pos] != '\0'))
        {
          if (buffer[pos] == '\n')
          {
            curr_line++;
          }

          if (err_line < SYNTAX_ERROR_CONTEXT_SIZE
              || (err_line >= curr_line
                  && (err_line - curr_line) <= SYNTAX_ERROR_CONTEXT_SIZE))
          {
            /* context must be printed */
            is_printing_context = true;
          }

          if (curr_line > err_line)
          {
            break;
          }

          if (is_printing_context)
          {
            jerry_port_log (JERRY_LOG_LEVEL_ERROR, "%c", buffer[pos]);
          }

          pos++;
        }

        jerry_port_log (JERRY_LOG_LEVEL_ERROR, "\n");

        while (--err_col)
        {
          jerry_port_log (JERRY_LOG_LEVEL_ERROR, "~");
        }

        jerry_port_log (JERRY_LOG_LEVEL_ERROR, "^\n");
      }
    }
  }

  jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Script Error: %s\n", err_str_buf);
  jerry_release_value (err_str_val);
}
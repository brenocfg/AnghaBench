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
typedef  int jerry_size_t ;
typedef  scalar_t__ jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int jerry_get_utf8_string_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_port_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_string_to_utf8_char_buffer (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_unhandled_exception (jerry_value_t error_value) /**< error value */
{
  assert (!jerry_value_is_error (error_value));

  jerry_value_t err_str_val = jerry_value_to_string (error_value);

  if (jerry_value_is_error (err_str_val))
  {
    /* Avoid recursive error throws. */
    jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Snapshot error: [value cannot be converted to string]\n");
    jerry_release_value (err_str_val);
    return;
  }

  jerry_size_t err_str_size = jerry_get_utf8_string_size (err_str_val);

  if (err_str_size >= 256)
  {
    jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Snapshot error: [value cannot be converted to string]\n");
    jerry_release_value (err_str_val);
    return;
  }

  jerry_char_t err_str_buf[256];
  jerry_size_t string_end = jerry_string_to_utf8_char_buffer (err_str_val, err_str_buf, err_str_size);
  assert (string_end == err_str_size);
  err_str_buf[string_end] = 0;

  jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Snapshot error: %s\n", (char *) err_str_buf);
  jerry_release_value (err_str_val);
}
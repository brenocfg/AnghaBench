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
typedef  int /*<<< orphan*/  jerry_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_VLA (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_char_t ; 
 int /*<<< orphan*/  jerry_create_number (int) ; 
 int /*<<< orphan*/  jerry_get_utf8_string_size (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  jerry_string_to_utf8_char_buffer (int /*<<< orphan*/  const,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ name_string ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
resolve_differently_handled_module (const jerry_value_t name,
                                    jerry_value_t *result)
{
  jerry_size_t name_size = jerry_get_utf8_string_size (name);
  JERRY_VLA (jerry_char_t, name_string, name_size);
  jerry_string_to_utf8_char_buffer (name, name_string, name_size);

  if (!strncmp ((char *) name_string, "differently-handled-module", name_size))
  {
    (*result) = jerry_create_number (29);
    return true;
  }
  return false;
}
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

/* Variables and functions */
 int /*<<< orphan*/  ACTUAL_NAME ; 
 int /*<<< orphan*/  JERRY_VLA (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  jerry_char_t ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int jerry_get_string_size (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  jerry_string_to_char_buffer (int /*<<< orphan*/  const,scalar_t__*,int) ; 
 scalar_t__* name_string ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
resolve (const jerry_value_t canonical_name, jerry_value_t *result)
{
  jerry_size_t name_size = jerry_get_string_size (canonical_name);
  JERRY_VLA (jerry_char_t, name_string, name_size + 1);
  jerry_string_to_char_buffer (canonical_name, name_string, name_size);
  name_string[name_size] = 0;

  if (!strcmp ((char *) name_string, ACTUAL_NAME))
  {
    *result = jerry_create_object ();
    return true;
  }
  return false;
}
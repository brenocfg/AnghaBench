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
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static jerry_value_t
set_property (const jerry_value_t obj_val, /**< object value */
              const char *str_p, /**< property name */
              const jerry_value_t val) /**< value to set */
{
  jerry_value_t prop_name_val = jerry_create_string ((const jerry_char_t *) str_p);
  jerry_value_t ret_val = jerry_set_property (obj_val, prop_name_val, val);
  jerry_release_value (prop_name_val);
  return ret_val;
}
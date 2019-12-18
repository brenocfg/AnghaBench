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

/* Variables and functions */
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_has_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
jerryx_module_check_cache (jerry_value_t cache, /**< cache from which to attempt to retrieve the module by name */
                           jerry_value_t module_name, /**< JerryScript string value holding the module name */
                           jerry_value_t *result) /**< Resulting value */
{
  bool ret = false;

  /* Check if the cache has the module. */
  jerry_value_t js_has_property = jerry_has_property (cache, module_name);

  /* If we succeed in getting an answer, we examine the answer. */
  if (!jerry_value_is_error (js_has_property))
  {
    bool has_property = jerry_get_boolean_value (js_has_property);

    /* If the module is indeed in the cache, we return it. */
    if (has_property)
    {
      if (result != NULL)
      {
        (*result) = jerry_get_property (cache, module_name);
      }
      ret = true;
    }
  }

  jerry_release_value (js_has_property);

  return ret;
}
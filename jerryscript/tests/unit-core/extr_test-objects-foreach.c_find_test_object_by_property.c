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
 int /*<<< orphan*/  jerry_acquire_value (int /*<<< orphan*/  const) ; 
 scalar_t__ jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_has_property (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
find_test_object_by_property (const jerry_value_t candidate,
                              void *context_p)
{
  jerry_value_t *args_p = (jerry_value_t *) context_p;
  jerry_value_t result = jerry_has_property (candidate, args_p[0]);

  bool has_property = (!jerry_value_is_error (result) && jerry_get_boolean_value (result));

  /* If the object has the desired property, store a new reference to it in args_p[1]. */
  if (has_property)
  {
    args_p[1] = jerry_acquire_value (candidate);
  }

  jerry_release_value (result);

  /* Stop iterating if we've found our object. */
  return !has_property;
}
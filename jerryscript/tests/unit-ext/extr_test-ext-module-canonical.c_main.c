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
typedef  int /*<<< orphan*/  jerryx_module_resolver_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 scalar_t__ ACTUAL_NAME ; 
 scalar_t__ ALIAS_NAME ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 scalar_t__ TEST_VALUE ; 
 int /*<<< orphan*/  canonical_test ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_number (scalar_t__) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/ *) ; 
 scalar_t__ jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_module_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

int
main (int argc, char **argv)
{
  (void) argc;
  (void) argv;

  const jerryx_module_resolver_t *resolver = &canonical_test;

  jerry_init (JERRY_INIT_EMPTY);

  jerry_value_t actual_name = jerry_create_string ((jerry_char_t *) ACTUAL_NAME);
  jerry_value_t alias_name = jerry_create_string ((jerry_char_t *) ALIAS_NAME);

  /* It's important that we resolve by the non-canonical name first. */
  jerry_value_t result2 = jerryx_module_resolve (alias_name, &resolver, 1);
  jerry_value_t result1 = jerryx_module_resolve (actual_name, &resolver, 1);
  jerry_release_value (actual_name);
  jerry_release_value (alias_name);

  /* An elaborate way of doing strict equal - set a property on one object and it "magically" appears on the other. */
  jerry_value_t prop_name = jerry_create_string ((jerry_char_t *) "something");
  jerry_value_t prop_value = jerry_create_number (TEST_VALUE);
  jerry_release_value (jerry_set_property (result1, prop_name, prop_value));
  jerry_release_value (prop_value);

  prop_value = jerry_get_property (result2, prop_name);
  TEST_ASSERT (jerry_get_number_value (prop_value) == TEST_VALUE);
  jerry_release_value (prop_value);

  jerry_release_value (prop_name);
  jerry_release_value (result1);
  jerry_release_value (result2);

  jerry_cleanup ();

  return 0;
}
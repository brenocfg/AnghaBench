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
typedef  int /*<<< orphan*/  pterodactylus ;
typedef  scalar_t__ jerry_value_t ;
typedef  char jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  compare_str (scalar_t__,char const*,size_t const) ; 
 scalar_t__ jerry_acquire_value (scalar_t__) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 scalar_t__ jerry_create_abort_from_value (scalar_t__,int) ; 
 scalar_t__ jerry_create_error_from_value (scalar_t__,int) ; 
 scalar_t__ jerry_create_number (int) ; 
 scalar_t__ jerry_create_object () ; 
 scalar_t__ jerry_create_string (char const*) ; 
 double jerry_get_number_value (scalar_t__) ; 
 scalar_t__ jerry_get_value_from_error (scalar_t__,int) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (scalar_t__) ; 
 int jerry_value_is_abort (scalar_t__) ; 
 int jerry_value_is_error (scalar_t__) ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  jerry_value_t obj_val = jerry_create_object ();
  obj_val = jerry_create_error_from_value (obj_val, true);
  jerry_value_t err_val = jerry_acquire_value (obj_val);

  obj_val = jerry_get_value_from_error (err_val, true);

  TEST_ASSERT (obj_val != err_val);
  jerry_release_value (err_val);
  jerry_release_value (obj_val);

  const jerry_char_t pterodactylus[] = "Pterodactylus";
  const size_t pterodactylus_size = sizeof (pterodactylus) - 1;

  jerry_value_t str = jerry_create_string (pterodactylus);
  jerry_value_t error = jerry_create_error_from_value (str, true);
  str = jerry_get_value_from_error (error, true);

  compare_str (str, pterodactylus, pterodactylus_size);
  jerry_release_value (str);

  str = jerry_create_string (pterodactylus);
  error = jerry_create_error_from_value (str, false);
  jerry_release_value (str);
  str = jerry_get_value_from_error (error, true);

  compare_str (str, pterodactylus, pterodactylus_size);
  jerry_release_value (str);

  str = jerry_create_string (pterodactylus);
  error = jerry_create_abort_from_value (str, true);
  str = jerry_get_value_from_error (error, true);

  compare_str (str, pterodactylus, pterodactylus_size);
  jerry_release_value (str);

  str = jerry_create_string (pterodactylus);
  error = jerry_create_abort_from_value (str, false);
  jerry_release_value (str);
  str = jerry_get_value_from_error (error, true);

  compare_str (str, pterodactylus, pterodactylus_size);
  jerry_release_value (str);

  str = jerry_create_string (pterodactylus);
  error = jerry_create_error_from_value (str, true);
  error = jerry_create_abort_from_value (error, true);
  TEST_ASSERT (jerry_value_is_abort (error));
  str = jerry_get_value_from_error (error, true);

  compare_str (str, pterodactylus, pterodactylus_size);
  jerry_release_value (str);

  str = jerry_create_string (pterodactylus);
  error = jerry_create_error_from_value (str, true);
  jerry_value_t error2 = jerry_create_abort_from_value (error, false);
  TEST_ASSERT (jerry_value_is_abort (error2));
  jerry_release_value (error);
  str = jerry_get_value_from_error (error2, true);

  compare_str (str, pterodactylus, pterodactylus_size);
  jerry_release_value (str);

  double test_num = 3.1415926;
  jerry_value_t num = jerry_create_number (test_num);
  jerry_value_t num2 = jerry_create_error_from_value (num, false);
  TEST_ASSERT (jerry_value_is_error (num2));
  jerry_release_value (num);
  num2 = jerry_get_value_from_error (num2, true);
  TEST_ASSERT (jerry_get_number_value (num2) == test_num);
  jerry_release_value (num2);

  num = jerry_create_number (test_num);
  num2 = jerry_create_error_from_value (num, true);
  TEST_ASSERT (jerry_value_is_error (num2));
  num2 = jerry_get_value_from_error (num2, true);
  TEST_ASSERT (jerry_get_number_value (num2) == test_num);
  jerry_release_value (num2);

  num = jerry_create_number (test_num);
  num2 = jerry_create_error_from_value (num, false);
  TEST_ASSERT (jerry_value_is_error (num2));
  jerry_release_value (num);
  jerry_value_t num3 = jerry_create_error_from_value (num2, false);
  TEST_ASSERT (jerry_value_is_error (num3));
  jerry_release_value (num2);
  num2 = jerry_get_value_from_error (num3, true);
  TEST_ASSERT (jerry_get_number_value (num2) == test_num);
  jerry_release_value (num2);

  num = jerry_create_number (test_num);
  num2 = jerry_create_error_from_value (num, true);
  TEST_ASSERT (jerry_value_is_error (num2));
  num3 = jerry_create_error_from_value (num2, true);
  TEST_ASSERT (jerry_value_is_error (num3));
  num2 = jerry_get_value_from_error (num3, true);
  TEST_ASSERT (jerry_get_number_value (num2) == test_num);
  jerry_release_value (num2);

  num = jerry_create_number (test_num);
  error = jerry_create_abort_from_value (num, true);
  TEST_ASSERT (jerry_value_is_abort (error));
  num2 = jerry_create_error_from_value (error, true);
  TEST_ASSERT (jerry_value_is_error (num2));
  num = jerry_get_value_from_error (num2, true);
  TEST_ASSERT (jerry_get_number_value (num) == test_num);
  jerry_release_value (num);

  num = jerry_create_number (test_num);
  error = jerry_create_abort_from_value (num, false);
  jerry_release_value (num);
  TEST_ASSERT (jerry_value_is_abort (error));
  num2 = jerry_create_error_from_value (error, true);
  TEST_ASSERT (jerry_value_is_error (num2));
  num = jerry_get_value_from_error (num2, true);
  TEST_ASSERT (jerry_get_number_value (num) == test_num);
  jerry_release_value (num);

  num = jerry_create_number (test_num);
  error = jerry_create_abort_from_value (num, true);
  TEST_ASSERT (jerry_value_is_abort (error));
  num2 = jerry_create_error_from_value (error, false);
  jerry_release_value (error);
  TEST_ASSERT (jerry_value_is_error (num2));
  num = jerry_get_value_from_error (num2, true);
  TEST_ASSERT (jerry_get_number_value (num) == test_num);
  jerry_release_value (num);

  num = jerry_create_number (test_num);
  error = jerry_create_abort_from_value (num, false);
  jerry_release_value (num);
  TEST_ASSERT (jerry_value_is_abort (error));
  num2 = jerry_create_error_from_value (error, false);
  jerry_release_value (error);
  TEST_ASSERT (jerry_value_is_error (num2));
  num = jerry_get_value_from_error (num2, true);
  TEST_ASSERT (jerry_get_number_value (num) == test_num);
  jerry_release_value (num);

  jerry_value_t value = jerry_create_number (42);
  value = jerry_get_value_from_error (value, true);
  jerry_release_value (value);

  value = jerry_create_number (42);
  jerry_value_t value2 = jerry_get_value_from_error (value, false);
  jerry_release_value (value);
  jerry_release_value (value2);

  value = jerry_create_number (42);
  error = jerry_create_error_from_value (value, true);
  error = jerry_create_error_from_value (error, true);
  jerry_release_value (error);

  value = jerry_create_number (42);
  error = jerry_create_abort_from_value (value, true);
  error = jerry_create_abort_from_value (error, true);
  jerry_release_value (error);

  value = jerry_create_number (42);
  error = jerry_create_error_from_value (value, true);
  error2 = jerry_create_error_from_value (error, false);
  jerry_release_value (error);
  jerry_release_value (error2);

  value = jerry_create_number (42);
  error = jerry_create_abort_from_value (value, true);
  error2 = jerry_create_abort_from_value (error, false);
  jerry_release_value (error);
  jerry_release_value (error2);

  jerry_cleanup ();
}
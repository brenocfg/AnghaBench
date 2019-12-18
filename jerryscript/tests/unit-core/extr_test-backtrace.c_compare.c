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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  size_t jerry_size_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_get_property_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t jerry_get_string_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 size_t jerry_string_to_char_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_string (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
compare (jerry_value_t array, /**< array */
         uint32_t index, /**< item index */
         const char *str) /**< string to compare */
{
  jerry_char_t buf[64];

  size_t len = strlen (str);

  TEST_ASSERT (len < sizeof (buf));

  jerry_value_t value = jerry_get_property_by_index (array, index);

  TEST_ASSERT (!jerry_value_is_error (value)
               && jerry_value_is_string (value));

  TEST_ASSERT (jerry_get_string_size (value) == len);

  jerry_size_t str_len = jerry_string_to_char_buffer (value, buf, (jerry_size_t) len);
  TEST_ASSERT (str_len == len);

  jerry_release_value (value);

  TEST_ASSERT (memcmp (buf, str, len) == 0);
}
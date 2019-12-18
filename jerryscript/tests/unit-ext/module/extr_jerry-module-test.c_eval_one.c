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
 int /*<<< orphan*/  JERRY_PARSE_STRICT_MODE ; 
 int /*<<< orphan*/  assert_number (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  jerry_eval (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
eval_one (const char *the_string, double expected_result)
{
  jerry_value_t js_eval_result = jerry_eval ((const jerry_char_t *) the_string,
                                             strlen (the_string),
                                             JERRY_PARSE_STRICT_MODE);
  assert_number (js_eval_result, expected_result);
  jerry_release_value (js_eval_result);
}
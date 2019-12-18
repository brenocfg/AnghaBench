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
typedef  scalar_t__ jerry_value_t ;
typedef  scalar_t__ jerry_length_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ERROR_TYPE ; 
 scalar_t__ jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static jerry_value_t
handler_throw_test (const jerry_value_t func_obj_val, /**< function object */
                    const jerry_value_t this_val, /**< this value */
                    const jerry_value_t args_p[], /**< arguments list */
                    const jerry_length_t args_cnt) /**< arguments length */
{
  printf ("ok %u %u %p %u\n",
          (unsigned int) func_obj_val, (unsigned int) this_val, (void *) args_p, (unsigned int) args_cnt);

  return jerry_create_error (JERRY_ERROR_TYPE, (jerry_char_t *) "error");
}
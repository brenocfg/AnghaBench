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
typedef  scalar_t__ lit_utf8_size_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_FINALIZE_UTF8_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_STRING_TO_UTF8_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_VALUE_UNDEFINED ; 
 int /*<<< orphan*/  code_utf8_buffer_p ; 
 int /*<<< orphan*/  code_utf8_buffer_size ; 
 int /*<<< orphan*/  ecma_op_eval_chars_buffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_string_get_size (int /*<<< orphan*/ *) ; 

ecma_value_t
ecma_op_eval (ecma_string_t *code_p, /**< code string */
              uint32_t parse_opts) /**< ecma_parse_opts_t option bits */
{
  ecma_value_t ret_value;

  lit_utf8_size_t chars_num = ecma_string_get_size (code_p);
  if (chars_num == 0)
  {
    ret_value = ECMA_VALUE_UNDEFINED;
  }
  else
  {
    ECMA_STRING_TO_UTF8_STRING (code_p, code_utf8_buffer_p, code_utf8_buffer_size);

    ret_value = ecma_op_eval_chars_buffer (code_utf8_buffer_p,
                                           chars_num,
                                           parse_opts);

    ECMA_FINALIZE_UTF8_STRING (code_utf8_buffer_p, code_utf8_buffer_size);
  }

  return ret_value;
}
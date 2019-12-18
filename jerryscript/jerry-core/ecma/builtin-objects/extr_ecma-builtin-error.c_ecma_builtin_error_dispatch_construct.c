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
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecma_builtin_error_dispatch_call (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_builtin_error_dispatch_construct (const ecma_value_t *arguments_list_p, /**< arguments list */
                                       ecma_length_t arguments_list_len) /**< number of arguments */
{
  return ecma_builtin_error_dispatch_call (arguments_list_p, arguments_list_len);
}
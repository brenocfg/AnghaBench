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

/* Variables and functions */
 int /*<<< orphan*/  ecma_builtin_helper_object_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ecma_value_t
ecma_builtin_object_prototype_object_to_string (ecma_value_t this_arg) /**< this argument */
{
  return ecma_builtin_helper_object_to_string (this_arg);
}
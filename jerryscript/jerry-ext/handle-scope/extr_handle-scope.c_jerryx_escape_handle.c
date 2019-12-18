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
typedef  int /*<<< orphan*/  jerryx_handle_scope_status ;
typedef  int /*<<< orphan*/  jerryx_escapable_handle_scope ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerryx_escape_handle_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

jerryx_handle_scope_status
jerryx_escape_handle (jerryx_escapable_handle_scope scope,
                      jerry_value_t escapee,
                      jerry_value_t *result)
{
  return jerryx_escape_handle_internal (scope, escapee, result, true);
}
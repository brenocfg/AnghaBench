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
typedef  int /*<<< orphan*/  jerryx_handle_scope ;

/* Variables and functions */
 int /*<<< orphan*/  jerryx_open_handle_scope (int /*<<< orphan*/ *) ; 

jerryx_handle_scope_status
jerryx_open_escapable_handle_scope (jerryx_handle_scope *result)
{
  return jerryx_open_handle_scope (result);
}
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

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_set_object_native_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  native_info ; 

__attribute__((used)) static jerry_value_t
create_object (void)
{
  jerry_value_t obj = jerry_create_object ();
  jerry_set_object_native_pointer (obj, NULL, &native_info);
  return obj;
}
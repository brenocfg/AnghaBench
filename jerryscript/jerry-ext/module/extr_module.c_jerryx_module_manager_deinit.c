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
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jerryx_module_manager_deinit (void *user_data_p) /**< context pointer to deinitialize */
{
  jerry_release_value (*(jerry_value_t *) user_data_p);
}
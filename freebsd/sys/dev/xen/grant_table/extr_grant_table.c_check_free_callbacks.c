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

/* Variables and functions */
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_free_callbacks () ; 
 int /*<<< orphan*/ * gnttab_free_callback_list ; 

__attribute__((used)) static inline void
check_free_callbacks(void)
{
	if (__predict_false(gnttab_free_callback_list != NULL))
		do_free_callbacks();
}
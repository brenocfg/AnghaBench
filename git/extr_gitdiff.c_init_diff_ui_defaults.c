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
 int /*<<< orphan*/  DIFF_DETECT_RENAME ; 
 int /*<<< orphan*/  diff_detect_rename_default ; 

void init_diff_ui_defaults(void)
{
	diff_detect_rename_default = DIFF_DETECT_RENAME;
}
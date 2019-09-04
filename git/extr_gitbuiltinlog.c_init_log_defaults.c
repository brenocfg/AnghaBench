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
 int /*<<< orphan*/  auto_decoration_style () ; 
 int /*<<< orphan*/  decoration_style ; 
 int /*<<< orphan*/  init_diff_ui_defaults () ; 
 int /*<<< orphan*/  init_grep_defaults (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void init_log_defaults(void)
{
	init_grep_defaults(the_repository);
	init_diff_ui_defaults();

	decoration_style = auto_decoration_style();
}
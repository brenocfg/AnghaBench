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
 int check_pager_config (char const*) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 scalar_t__ pager_in_use () ; 
 int use_pager ; 

void setup_auto_pager(const char *cmd, int def)
{
	if (use_pager != -1 || pager_in_use())
		return;
	use_pager = check_pager_config(cmd);
	if (use_pager == -1)
		use_pager = def;
	commit_pager_choice();
}
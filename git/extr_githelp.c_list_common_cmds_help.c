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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  common_categories ; 
 int /*<<< orphan*/  print_cmd_by_category (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

void list_common_cmds_help(void)
{
	puts(_("These are common Git commands used in various situations:"));
	print_cmd_by_category(common_categories, NULL);
}
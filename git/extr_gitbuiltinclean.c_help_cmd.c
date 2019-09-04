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
 int /*<<< orphan*/  CLEAN_COLOR_HELP ; 
 int /*<<< orphan*/  CLEAN_COLOR_RESET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  clean_print_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int help_cmd(void)
{
	clean_print_color(CLEAN_COLOR_HELP);
	printf_ln(_(
		    "clean               - start cleaning\n"
		    "filter by pattern   - exclude items from deletion\n"
		    "select by numbers   - select items to be deleted by numbers\n"
		    "ask each            - confirm each deletion (like \"rm -i\")\n"
		    "quit                - stop cleaning\n"
		    "help                - this screen\n"
		    "?                   - help for prompt selection"
		   ));
	clean_print_color(CLEAN_COLOR_RESET);
	return 0;
}
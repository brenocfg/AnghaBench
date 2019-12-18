#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct option {struct line_opt_callback_data* value; } ;
struct line_opt_callback_data {int /*<<< orphan*/  args; TYPE_1__* rev; } ;
struct TYPE_2__ {int line_level_traverse; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int log_line_range_callback(const struct option *option, const char *arg, int unset)
{
	struct line_opt_callback_data *data = option->value;

	BUG_ON_OPT_NEG(unset);

	if (!arg)
		return -1;

	data->rev->line_level_traverse = 1;
	string_list_append(&data->args, arg);

	return 0;
}
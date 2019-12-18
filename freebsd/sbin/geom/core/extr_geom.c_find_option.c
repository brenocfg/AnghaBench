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
struct g_option {char go_char; int /*<<< orphan*/ * go_name; } ;
struct g_command {struct g_option* gc_options; } ;

/* Variables and functions */

__attribute__((used)) static struct g_option *
find_option(struct g_command *cmd, char ch)
{
	struct g_option *opt;
	unsigned i;

	for (i = 0; ; i++) {
		opt = &cmd->gc_options[i];
		if (opt->go_name == NULL)
			return (NULL);
		if (opt->go_char == ch)
			return (opt);
	}
	/* NOTREACHED */
	return (NULL);
}
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
struct option {struct diff_options* value; } ;
struct diff_options {scalar_t__ color_moved; } ;

/* Variables and functions */
 scalar_t__ COLOR_MOVED_DEFAULT ; 
 scalar_t__ COLOR_MOVED_NO ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ diff_color_moved_default ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int parse_color_moved (char const*) ; 

__attribute__((used)) static int diff_opt_color_moved(const struct option *opt,
				const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	if (unset) {
		options->color_moved = COLOR_MOVED_NO;
	} else if (!arg) {
		if (diff_color_moved_default)
			options->color_moved = diff_color_moved_default;
		if (options->color_moved == COLOR_MOVED_NO)
			options->color_moved = COLOR_MOVED_DEFAULT;
	} else {
		int cm = parse_color_moved(arg);
		if (cm < 0)
			return error(_("bad --color-moved argument: %s"), arg);
		options->color_moved = cm;
	}
	return 0;
}
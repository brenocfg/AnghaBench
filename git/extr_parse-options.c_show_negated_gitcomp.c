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
struct option {int type; char const* long_name; int flags; } ;

/* Variables and functions */
#define  OPTION_BIT 136 
#define  OPTION_CALLBACK 135 
#define  OPTION_COUNTUP 134 
 int OPTION_END ; 
#define  OPTION_FILENAME 133 
#define  OPTION_INTEGER 132 
#define  OPTION_MAGNITUDE 131 
#define  OPTION_NEGBIT 130 
#define  OPTION_SET_INT 129 
#define  OPTION_STRING 128 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_NOCOMPLETE ; 
 int PARSE_OPT_NONEG ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

__attribute__((used)) static void show_negated_gitcomp(const struct option *opts, int nr_noopts)
{
	int printed_dashdash = 0;

	for (; opts->type != OPTION_END; opts++) {
		int has_unset_form = 0;
		const char *name;

		if (!opts->long_name)
			continue;
		if (opts->flags & (PARSE_OPT_HIDDEN | PARSE_OPT_NOCOMPLETE))
			continue;
		if (opts->flags & PARSE_OPT_NONEG)
			continue;

		switch (opts->type) {
		case OPTION_STRING:
		case OPTION_FILENAME:
		case OPTION_INTEGER:
		case OPTION_MAGNITUDE:
		case OPTION_CALLBACK:
		case OPTION_BIT:
		case OPTION_NEGBIT:
		case OPTION_COUNTUP:
		case OPTION_SET_INT:
			has_unset_form = 1;
			break;
		default:
			break;
		}
		if (!has_unset_form)
			continue;

		if (skip_prefix(opts->long_name, "no-", &name)) {
			if (nr_noopts < 0)
				printf(" --%s", name);
		} else if (nr_noopts >= 0) {
			if (nr_noopts && !printed_dashdash) {
				printf(" --");
				printed_dashdash = 1;
			}
			printf(" --no-%s", opts->long_name);
			nr_noopts++;
		}
	}
}
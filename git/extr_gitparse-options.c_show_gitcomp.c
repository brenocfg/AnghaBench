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
struct option {int type; char* long_name; int flags; } ;

/* Variables and functions */
#define  OPTION_CALLBACK 133 
 int OPTION_END ; 
#define  OPTION_FILENAME 132 
#define  OPTION_GROUP 131 
#define  OPTION_INTEGER 130 
#define  OPTION_MAGNITUDE 129 
#define  OPTION_STRING 128 
 int PARSE_OPT_COMPLETE ; 
 int PARSE_OPT_COMP_ARG ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_LASTARG_DEFAULT ; 
 int PARSE_OPT_NOARG ; 
 int PARSE_OPT_NOCOMPLETE ; 
 int PARSE_OPT_OPTARG ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 int /*<<< orphan*/  show_negated_gitcomp (struct option const*,int) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int show_gitcomp(const struct option *opts)
{
	const struct option *original_opts = opts;
	int nr_noopts = 0;

	for (; opts->type != OPTION_END; opts++) {
		const char *suffix = "";

		if (!opts->long_name)
			continue;
		if (opts->flags & (PARSE_OPT_HIDDEN | PARSE_OPT_NOCOMPLETE))
			continue;

		switch (opts->type) {
		case OPTION_GROUP:
			continue;
		case OPTION_STRING:
		case OPTION_FILENAME:
		case OPTION_INTEGER:
		case OPTION_MAGNITUDE:
		case OPTION_CALLBACK:
			if (opts->flags & PARSE_OPT_NOARG)
				break;
			if (opts->flags & PARSE_OPT_OPTARG)
				break;
			if (opts->flags & PARSE_OPT_LASTARG_DEFAULT)
				break;
			suffix = "=";
			break;
		default:
			break;
		}
		if (opts->flags & PARSE_OPT_COMP_ARG)
			suffix = "=";
		if (starts_with(opts->long_name, "no-"))
			nr_noopts++;
		printf(" --%s%s", opts->long_name, suffix);
	}
	show_negated_gitcomp(original_opts, -1);
	show_negated_gitcomp(original_opts, nr_noopts);
	fputc('\n', stdout);
	return PARSE_OPT_COMPLETE;
}
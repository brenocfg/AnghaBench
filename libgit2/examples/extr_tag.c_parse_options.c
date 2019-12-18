#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* tag_name; char const* target; int num_lines; int force; char const* pattern; char const* message; } ;
typedef  TYPE_1__ tag_options ;
typedef  int /*<<< orphan*/ * tag_action ;
struct TYPE_8__ {int pos; } ;
typedef  TYPE_2__ args_info ;

/* Variables and functions */
 TYPE_2__ ARGS_INFO_INIT ; 
 int /*<<< orphan*/  action_create_lighweight_tag ; 
 int /*<<< orphan*/  action_create_tag ; 
 int /*<<< orphan*/  action_delete_tag ; 
 int /*<<< orphan*/  action_list_tags ; 
 scalar_t__ match_int_arg (int*,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_str_arg (char const**,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void parse_options(tag_action *action, tag_options *opts, int argc, char **argv)
{
	args_info args = ARGS_INFO_INIT;
	*action = &action_list_tags;

	for (args.pos = 1; args.pos < argc; ++args.pos) {
		const char *curr = argv[args.pos];

		if (curr[0] != '-') {
			if (!opts->tag_name)
				opts->tag_name = curr;
			else if (!opts->target)
				opts->target = curr;
			else
				print_usage();

			if (*action != &action_create_tag)
				*action = &action_create_lighweight_tag;
		} else if (!strcmp(curr, "-n")) {
			opts->num_lines = 1;
			*action = &action_list_tags;
		} else if (!strcmp(curr, "-a")) {
			*action = &action_create_tag;
		} else if (!strcmp(curr, "-f")) {
			opts->force = 1;
		} else if (match_int_arg(&opts->num_lines, &args, "-n", 0)) {
			*action = &action_list_tags;
		} else if (match_str_arg(&opts->pattern, &args, "-l")) {
			*action = &action_list_tags;
		} else if (match_str_arg(&opts->tag_name, &args, "-d")) {
			*action = &action_delete_tag;
		} else if (match_str_arg(&opts->message, &args, "-m")) {
			*action = &action_create_tag;
		}
	}
}
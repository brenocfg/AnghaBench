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
struct option {int dummy; } ;

/* Variables and functions */
 struct option OPT_END () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  default_notes_ref () ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_notes_get_ref_usage ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

__attribute__((used)) static int get_ref(int argc, const char **argv, const char *prefix)
{
	struct option options[] = { OPT_END() };
	argc = parse_options(argc, argv, prefix, options,
			     git_notes_get_ref_usage, 0);

	if (argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_get_ref_usage, options);
	}

	puts(default_notes_ref());
	return 0;
}
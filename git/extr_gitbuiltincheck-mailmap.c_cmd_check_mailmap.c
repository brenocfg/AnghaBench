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
struct string_list {int dummy; } ;
struct strbuf {char const* buf; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_mailmap (struct string_list*,char const*) ; 
 int /*<<< orphan*/  check_mailmap_options ; 
 int /*<<< orphan*/  check_mailmap_usage ; 
 int /*<<< orphan*/  clear_mailmap (struct string_list*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  maybe_flush_or_die (int /*<<< orphan*/ ,char*) ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_mailmap (struct string_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ use_stdin ; 

int cmd_check_mailmap(int argc, const char **argv, const char *prefix)
{
	int i;
	struct string_list mailmap = STRING_LIST_INIT_NODUP;

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, check_mailmap_options,
			     check_mailmap_usage, 0);
	if (argc == 0 && !use_stdin)
		die(_("no contacts specified"));

	read_mailmap(&mailmap, NULL);

	for (i = 0; i < argc; ++i)
		check_mailmap(&mailmap, argv[i]);
	maybe_flush_or_die(stdout, "stdout");

	if (use_stdin) {
		struct strbuf buf = STRBUF_INIT;
		while (strbuf_getline_lf(&buf, stdin) != EOF) {
			check_mailmap(&mailmap, buf.buf);
			maybe_flush_or_die(stdout, "stdout");
		}
		strbuf_release(&buf);
	}

	clear_mailmap(&mailmap);
	return 0;
}
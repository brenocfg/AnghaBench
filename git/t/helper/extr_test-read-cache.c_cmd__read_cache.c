#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFRESH_QUIET ; 
 scalar_t__ ce_uptodate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  discard_cache () ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int index_name_pos (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  refresh_index (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ the_index ; 
 int /*<<< orphan*/  write_file (char const*,char*,int) ; 

int cmd__read_cache(int argc, const char **argv)
{
	int i, cnt = 1;
	const char *name = NULL;

	if (argc > 1 && skip_prefix(argv[1], "--print-and-refresh=", &name)) {
		argc--;
		argv++;
	}

	if (argc == 2)
		cnt = strtol(argv[1], NULL, 0);
	setup_git_directory();
	git_config(git_default_config, NULL);
	for (i = 0; i < cnt; i++) {
		read_cache();
		if (name) {
			int pos;

			refresh_index(&the_index, REFRESH_QUIET,
				      NULL, NULL, NULL);
			pos = index_name_pos(&the_index, name, strlen(name));
			if (pos < 0)
				die("%s not in index", name);
			printf("%s is%s up to date\n", name,
			       ce_uptodate(the_index.cache[pos]) ? "" : " not");
			write_file(name, "%d\n", i);
		}
		discard_cache();
	}
	return 0;
}
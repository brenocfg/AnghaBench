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
struct tempfile {int dummy; } ;
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option const OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  delete_tempfile (struct tempfile**) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 int /*<<< orphan*/  init_socket_directory (char const*) ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option const*,char const**,int /*<<< orphan*/ ) ; 
 struct tempfile* register_tempfile (char const*) ; 
 int /*<<< orphan*/  serve_cache (char const*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (char const**,struct option const*) ; 

int cmd_main(int argc, const char **argv)
{
	struct tempfile *socket_file;
	const char *socket_path;
	int ignore_sighup = 0;
	static const char *usage[] = {
		"git-credential-cache--daemon [opts] <socket_path>",
		NULL
	};
	int debug = 0;
	const struct option options[] = {
		OPT_BOOL(0, "debug", &debug,
			 N_("print debugging messages to stderr")),
		OPT_END()
	};

	git_config_get_bool("credentialcache.ignoresighup", &ignore_sighup);

	argc = parse_options(argc, argv, NULL, options, usage, 0);
	socket_path = argv[0];

	if (!socket_path)
		usage_with_options(usage, options);

	if (!is_absolute_path(socket_path))
		die("socket directory must be an absolute path");

	init_socket_directory(socket_path);
	socket_file = register_tempfile(socket_path);

	if (ignore_sighup)
		signal(SIGHUP, SIG_IGN);

	serve_cache(socket_path, debug);
	delete_tempfile(&socket_file);

	return 0;
}
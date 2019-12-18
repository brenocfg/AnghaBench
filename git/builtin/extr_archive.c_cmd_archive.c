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
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_END () ; 
 struct option OPT_FILENAME (char,char*,char const**,int /*<<< orphan*/ ) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_ALL ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  create_output_file (char const*) ; 
 int /*<<< orphan*/  init_archivers () ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int run_remote_archiver (int,char const**,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  the_repository ; 
 int write_archive (int,char const**,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int cmd_archive(int argc, const char **argv, const char *prefix)
{
	const char *exec = "git-upload-archive";
	const char *output = NULL;
	const char *remote = NULL;
	struct option local_opts[] = {
		OPT_FILENAME('o', "output", &output,
			     N_("write the archive to this file")),
		OPT_STRING(0, "remote", &remote, N_("repo"),
			N_("retrieve the archive from remote repository <repo>")),
		OPT_STRING(0, "exec", &exec, N_("command"),
			N_("path to the remote git-upload-archive command")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, local_opts, NULL,
			     PARSE_OPT_KEEP_ALL);

	init_archivers();

	if (output)
		create_output_file(output);

	if (remote)
		return run_remote_archiver(argc, argv, remote, exec, output);

	setvbuf(stderr, NULL, _IOLBF, BUFSIZ);

	return write_archive(argc, argv, prefix, the_repository, output, 0);
}
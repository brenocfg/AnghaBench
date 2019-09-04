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
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  MAX_ARGS ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  enter_repo (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_archivers () ; 
 char* packet_read_line (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  starts_with (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  upload_archive_usage ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int write_archive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int cmd_upload_archive_writer(int argc, const char **argv, const char *prefix)
{
	struct argv_array sent_argv = ARGV_ARRAY_INIT;
	const char *arg_cmd = "argument ";

	if (argc != 2 || !strcmp(argv[1], "-h"))
		usage(upload_archive_usage);

	if (!enter_repo(argv[1], 0))
		die("'%s' does not appear to be a git repository", argv[1]);

	init_archivers();

	/* put received options in sent_argv[] */
	argv_array_push(&sent_argv, "git-upload-archive");
	for (;;) {
		char *buf = packet_read_line(0, NULL);
		if (!buf)
			break;	/* got a flush */
		if (sent_argv.argc > MAX_ARGS)
			die("Too many options (>%d)", MAX_ARGS - 1);

		if (!starts_with(buf, arg_cmd))
			die("'argument' token or flush expected");
		argv_array_push(&sent_argv, buf + strlen(arg_cmd));
	}

	/* parse all options sent by the client */
	return write_archive(sent_argv.argc, sent_argv.argv, prefix,
			     the_repository, NULL, 1);
}
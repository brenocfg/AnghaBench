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
struct mailinfo {char const* metainfo_charset; int keep_subject; int keep_non_patch_brackets_in_subject; int add_message_id; int use_scissors; int /*<<< orphan*/  output; int /*<<< orphan*/  input; scalar_t__ use_inbody_headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_mailinfo (struct mailinfo*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_commit_output_encoding () ; 
 int /*<<< orphan*/  mailinfo (struct mailinfo*,char*,char*) ; 
 int /*<<< orphan*/  mailinfo_usage ; 
 char* prefix_filename (char const*,char const*) ; 
 int /*<<< orphan*/  setup_mailinfo (struct mailinfo*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int cmd_mailinfo(int argc, const char **argv, const char *prefix)
{
	const char *def_charset;
	struct mailinfo mi;
	int status;
	char *msgfile, *patchfile;

	setup_mailinfo(&mi);

	def_charset = get_commit_output_encoding();
	mi.metainfo_charset = def_charset;

	while (1 < argc && argv[1][0] == '-') {
		if (!strcmp(argv[1], "-k"))
			mi.keep_subject = 1;
		else if (!strcmp(argv[1], "-b"))
			mi.keep_non_patch_brackets_in_subject = 1;
		else if (!strcmp(argv[1], "-m") || !strcmp(argv[1], "--message-id"))
			mi.add_message_id = 1;
		else if (!strcmp(argv[1], "-u"))
			mi.metainfo_charset = def_charset;
		else if (!strcmp(argv[1], "-n"))
			mi.metainfo_charset = NULL;
		else if (starts_with(argv[1], "--encoding="))
			mi.metainfo_charset = argv[1] + 11;
		else if (!strcmp(argv[1], "--scissors"))
			mi.use_scissors = 1;
		else if (!strcmp(argv[1], "--no-scissors"))
			mi.use_scissors = 0;
		else if (!strcmp(argv[1], "--no-inbody-headers"))
			mi.use_inbody_headers = 0;
		else
			usage(mailinfo_usage);
		argc--; argv++;
	}

	if (argc != 3)
		usage(mailinfo_usage);

	mi.input = stdin;
	mi.output = stdout;

	msgfile = prefix_filename(prefix, argv[1]);
	patchfile = prefix_filename(prefix, argv[2]);

	status = !!mailinfo(&mi, msgfile, patchfile);
	clear_mailinfo(&mi);

	free(msgfile);
	free(patchfile);
	return status;
}
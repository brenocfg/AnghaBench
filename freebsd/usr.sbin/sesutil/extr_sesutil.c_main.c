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
struct command {int (* exec ) (int,char**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct command* cmds ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nbcmds ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int,char**) ; 
 char* uflag ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int xo_parse_args (int,char**) ; 

int
main(int argc, char **argv)
{
	int i, ch;
	struct command *cmd = NULL;

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);

	uflag = "/dev/ses[0-9]*";
	while ((ch = getopt_long(argc, argv, "u:", NULL, NULL)) != -1) {
		switch (ch) {
		case 'u':
			uflag = optarg;
			break;
		case '?':
		default:
			usage(stderr, NULL);
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1) {
		warnx("Missing command");
		usage(stderr, NULL);
	}

	for (i = 0; i < nbcmds; i++) {
		if (strcmp(argv[0], cmds[i].name) == 0) {
			cmd = &cmds[i];
			break;
		}
	}

	if (cmd == NULL) {
		warnx("unknown command %s", argv[0]);
		usage(stderr, NULL);
	}

	return (cmd->exec(argc, argv));
}
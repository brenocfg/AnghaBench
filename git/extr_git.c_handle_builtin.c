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
struct cmd_struct {int dummy; } ;
struct argv_array {char** argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct cmd_struct* get_builtin (char const*) ; 
 int /*<<< orphan*/  run_builtin (struct cmd_struct*,int,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strip_extension (char const**) ; 

__attribute__((used)) static void handle_builtin(int argc, const char **argv)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	const char *cmd;
	struct cmd_struct *builtin;

	strip_extension(argv);
	cmd = argv[0];

	/* Turn "git cmd --help" into "git help --exclude-guides cmd" */
	if (argc > 1 && !strcmp(argv[1], "--help")) {
		int i;

		argv[1] = argv[0];
		argv[0] = cmd = "help";

		for (i = 0; i < argc; i++) {
			argv_array_push(&args, argv[i]);
			if (!i)
				argv_array_push(&args, "--exclude-guides");
		}

		argc++;
		argv = args.argv;
	}

	builtin = get_builtin(cmd);
	if (builtin)
		exit(run_builtin(builtin, argc, argv));
	argv_array_clear(&args);
}
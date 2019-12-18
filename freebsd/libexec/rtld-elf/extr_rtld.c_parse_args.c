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

/* Variables and functions */
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtld_error (char*,char const*) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int parse_integer (char*) ; 
 int /*<<< orphan*/  print_usage (char*) ; 
 int /*<<< orphan*/  rtld_die () ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
parse_args(char* argv[], int argc, bool *use_pathp, int *fdp)
{
	const char *arg;
	int fd, i, j, arglen;
	char opt;

	dbg("Parsing command-line arguments");
	*use_pathp = false;
	*fdp = -1;

	for (i = 1; i < argc; i++ ) {
		arg = argv[i];
		dbg("argv[%d]: '%s'", i, arg);

		/*
		 * rtld arguments end with an explicit "--" or with the first
		 * non-prefixed argument.
		 */
		if (strcmp(arg, "--") == 0) {
			i++;
			break;
		}
		if (arg[0] != '-')
			break;

		/*
		 * All other arguments are single-character options that can
		 * be combined, so we need to search through `arg` for them.
		 */
		arglen = strlen(arg);
		for (j = 1; j < arglen; j++) {
			opt = arg[j];
			if (opt == 'h') {
				print_usage(argv[0]);
				_exit(0);
			} else if (opt == 'f') {
			/*
			 * -f XX can be used to specify a descriptor for the
			 * binary named at the command line (i.e., the later
			 * argument will specify the process name but the
			 * descriptor is what will actually be executed)
			 */
			if (j != arglen - 1) {
				/* -f must be the last option in, e.g., -abcf */
				_rtld_error("Invalid options: %s", arg);
				rtld_die();
			}
			i++;
			fd = parse_integer(argv[i]);
			if (fd == -1) {
				_rtld_error("Invalid file descriptor: '%s'",
				    argv[i]);
				rtld_die();
			}
			*fdp = fd;
			break;
			} else if (opt == 'p') {
				*use_pathp = true;
			} else {
				_rtld_error("Invalid argument: '%s'", arg);
				print_usage(argv[0]);
				rtld_die();
			}
		}
	}

	return (i);
}
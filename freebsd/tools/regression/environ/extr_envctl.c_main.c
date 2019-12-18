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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  blank_env (char*) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  dump_environ () ; 
 char** environ ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 char getopt (int,char**,char*) ; 
 char* optarg ; 
 size_t optind ; 
 int /*<<< orphan*/  print_rtrn_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char **argv)
{
	char arg;
	const char *eol = "\n";
	const char *value;
	static char *emptyEnv[] = { NULL };
	static char *staticEnv[] = { "FOO=bar", NULL };

	if (argc == 1) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* The entire program is basically executed from this loop. */
	while ((arg = getopt(argc, argv, "DGS:Ub:c:g:hp:rs:tu:")) != -1) {
		switch (arg) {
		case 'b':
			blank_env(optarg);
			break;

		case 'c':
			switch (atoi(optarg)) {
			case 1:
				environ = NULL;
				break;

			case 2:
				environ[0] = NULL;
				break;

			case 3:
				environ = calloc(1, sizeof(*environ));
				break;

			case 4:
				environ = emptyEnv;
				break;
			}
			break;

		case 'D':
			dump_environ();
			break;

		case 'G':
		case 'g':
			value = getenv(arg == 'g' ? optarg : NULL);
			printf("%s%s", value == NULL ? "*NULL*" : value, eol);
			break;

		case 'p':
			print_rtrn_errno(putenv(optarg), eol);
			break;

		case 'r':
			environ = staticEnv;
			break;

		case 'S':
			print_rtrn_errno(setenv(NULL, optarg,
			    atoi(argv[optind])), eol);
			optind += 1;
			break;

		case 's':
			print_rtrn_errno(setenv(optarg, argv[optind],
			    atoi(argv[optind + 1])), eol);
			optind += 2;
			break;

		case 't':
			eol = " ";
			break;

		case 'U':
		case 'u':
			print_rtrn_errno(unsetenv(arg == 'u' ? optarg : NULL),
			    eol);
			break;

		case 'h':
		default:
			usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	/* Output a closing newline in test mode. */
	if (eol[0] == ' ')
		printf("\n");

	return (EXIT_SUCCESS);
}
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
struct pe_opts {int capture_stdout; int capture_stderr; int return_prog_exit_status; int expose_authtok; int use_first_pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAM_LOG_DEBUG ; 
 int /*<<< orphan*/  memset (struct pe_opts*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
parse_options(const char *func, int *argc, const char **argv[],
    struct pe_opts *options)
{
	int i;

	/*
	 * Parse options:
	 *   return_prog_exit_status:
	 *     use the program exit status as the return code of pam_exec
	 *   --:
	 *     stop options parsing; what follows is the command to execute
	 */
	memset(options, 0, sizeof(*options));

	for (i = 0; i < *argc; ++i) {
		if (strcmp((*argv)[i], "debug") == 0 ||
		    strcmp((*argv)[i], "no_warn") == 0) {
			/* ignore */
		} else if (strcmp((*argv)[i], "capture_stdout") == 0) {
			options->capture_stdout = 1;
		} else if (strcmp((*argv)[i], "capture_stderr") == 0) {
			options->capture_stderr = 1;
		} else if (strcmp((*argv)[i], "return_prog_exit_status") == 0) {
			options->return_prog_exit_status = 1;
		} else if (strcmp((*argv)[i], "expose_authtok") == 0) {
			options->expose_authtok = 1;
		} else if (strcmp((*argv)[i], "use_first_pass") == 0) {
			options->use_first_pass = 1;
		} else {
			if (strcmp((*argv)[i], "--") == 0) {
				(*argc)--;
				(*argv)++;
			}
			break;
		}
		openpam_log(PAM_LOG_DEBUG, "%s: option \"%s\" enabled",
		    func, (*argv)[i]);
	}

	(*argc) -= i;
	(*argv) += i;

	return (0);
}
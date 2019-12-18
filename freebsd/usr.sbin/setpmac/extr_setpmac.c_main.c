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
typedef  int /*<<< orphan*/  mac_t ;

/* Variables and functions */
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  execlp (char const*,char const*,char*,char*) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  mac_free (int /*<<< orphan*/ ) ; 
 int mac_from_text (int /*<<< orphan*/ *,char*) ; 
 int mac_set_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	const char *shell;
	mac_t label;
	int error;


	if (argc < 3)
		usage();

	error = mac_from_text(&label, argv[1]);
	if (error != 0) {
		perror("mac_from_text");
		return (-1);
	}

	error = mac_set_proc(label);
	if (error != 0) {
		perror(argv[1]);
		return (-1);
	}

	mac_free(label);

	if (argc >= 3) {
		execvp(argv[2], argv + 2);
		err(1, "%s", argv[2]);
	} else {
		if (!(shell = getenv("SHELL")))
			shell = _PATH_BSHELL;
		execlp(shell, shell, "-i", (char *)NULL);
		err(1, "%s", shell);
	}
	/* NOTREACHED */
}
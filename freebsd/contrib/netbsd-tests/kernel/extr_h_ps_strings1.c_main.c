#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nenv_err ;
typedef  int /*<<< orphan*/  nargv_err ;
typedef  int /*<<< orphan*/  env_err ;
typedef  int /*<<< orphan*/  argv_err ;
struct TYPE_2__ {int ps_nargvstr; char** ps_argvstr; char** ps_envstr; int ps_nenvstr; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 TYPE_1__* __ps_strings ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char const*,int) ; 

int
main(int argc, char **argv, char **environ)
{
	int ret = 0;
	int nenv;

	if (__ps_strings->ps_nargvstr != argc) {
		static const char nargv_err[] = "Wrong argc in ps_strings";
		write(STDOUT_FILENO, nargv_err, sizeof(nargv_err));
		ret = 1;
	}

	if (__ps_strings->ps_argvstr != argv) {
		static const char argv_err[] = "Wrong argv in ps_strings";
		write(STDOUT_FILENO, argv_err, sizeof(argv_err));
		ret = 1;
	}

	if (__ps_strings->ps_envstr != environ) {
		static const char env_err[] = "Wrong env in ps_strings";
		write(STDOUT_FILENO, env_err, sizeof(env_err));
		ret = 1;
	}
	nenv = 0;
	while (environ[nenv])
		++nenv;
	if (__ps_strings->ps_nenvstr != nenv) {
		static const char nenv_err[] = "Wrong nenv in ps_strings";
		write(STDOUT_FILENO, nenv_err, sizeof(nenv_err));
		ret = 1;
	}

	return ret;
}
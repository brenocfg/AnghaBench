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
struct posix_spawn_args {char** envp; scalar_t__ error; int /*<<< orphan*/  argv; int /*<<< orphan*/  path; scalar_t__ use_env_path; int /*<<< orphan*/ * fa; int /*<<< orphan*/ * sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  _execve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char* const*) ; 
 int /*<<< orphan*/  _execvpe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char* const*) ; 
 int /*<<< orphan*/  _exit (int) ; 
 char** environ ; 
 scalar_t__ errno ; 
 scalar_t__ process_file_actions (int /*<<< orphan*/ ) ; 
 scalar_t__ process_spawnattr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_posix_spawn_thr(void *data)
{
	struct posix_spawn_args *psa;
	char * const *envp;

	psa = data;
	if (psa->sa != NULL) {
		psa->error = process_spawnattr(*psa->sa);
		if (psa->error)
			_exit(127);
	}
	if (psa->fa != NULL) {
		psa->error = process_file_actions(*psa->fa);
		if (psa->error)
			_exit(127);
	}
	envp = psa->envp != NULL ? psa->envp : environ;
	if (psa->use_env_path)
		_execvpe(psa->path, psa->argv, envp);
	else
		_execve(psa->path, psa->argv, envp);
	psa->error = errno;

	/* This is called in such a way that it must not exit. */
	_exit(127);
}
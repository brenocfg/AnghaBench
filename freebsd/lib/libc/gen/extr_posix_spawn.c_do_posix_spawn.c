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
struct posix_spawn_args {char const* path; char* const* argv; char* const* envp; int use_env_path; scalar_t__ error; int /*<<< orphan*/  const* sa; int /*<<< orphan*/  const* fa; } ;
typedef  int /*<<< orphan*/  posix_spawnattr_t ;
typedef  int /*<<< orphan*/  posix_spawn_file_actions_t ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RFSPAWN ; 
 int /*<<< orphan*/  WNOHANG ; 
 int _RFORK_THREAD_STACK_SIZE ; 
 int /*<<< orphan*/  _posix_spawn_thr (struct posix_spawn_args*) ; 
 int /*<<< orphan*/  _waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int rfork (int /*<<< orphan*/ ) ; 
 int rfork_thread (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  (*) (struct posix_spawn_args*),struct posix_spawn_args*) ; 
 int vfork () ; 

__attribute__((used)) static int
do_posix_spawn(pid_t *pid, const char *path,
    const posix_spawn_file_actions_t *fa,
    const posix_spawnattr_t *sa,
    char * const argv[], char * const envp[], int use_env_path)
{
	struct posix_spawn_args psa;
	pid_t p;
#ifdef _RFORK_THREAD_STACK_SIZE
	char *stack;

	stack = malloc(_RFORK_THREAD_STACK_SIZE);
	if (stack == NULL)
		return (ENOMEM);
#endif
	psa.path = path;
	psa.fa = fa;
	psa.sa = sa;
	psa.argv = argv;
	psa.envp = envp;
	psa.use_env_path = use_env_path;
	psa.error = 0;

	/*
	 * Passing RFSPAWN to rfork(2) gives us effectively a vfork that drops
	 * non-ignored signal handlers.  We'll fall back to the slightly less
	 * ideal vfork(2) if we get an EINVAL from rfork -- this should only
	 * happen with newer libc on older kernel that doesn't accept
	 * RFSPAWN.
	 */
#ifdef _RFORK_THREAD_STACK_SIZE
	/*
	 * x86 stores the return address on the stack, so rfork(2) cannot work
	 * as-is because the child would clobber the return address om the
	 * parent.  Because of this, we must use rfork_thread instead while
	 * almost every other arch stores the return address in a register.
	 */
	p = rfork_thread(RFSPAWN, stack + _RFORK_THREAD_STACK_SIZE,
	    _posix_spawn_thr, &psa);
	free(stack);
#else
	p = rfork(RFSPAWN);
	if (p == 0)
		/* _posix_spawn_thr does not return */
		_posix_spawn_thr(&psa);
#endif
	/*
	 * The above block should leave us in a state where we've either
	 * succeeded and we're ready to process the results, or we need to
	 * fallback to vfork() if the kernel didn't like RFSPAWN.
	 */

	if (p == -1 && errno == EINVAL) {
		p = vfork();
		if (p == 0)
			/* _posix_spawn_thr does not return */
			_posix_spawn_thr(&psa);
	}
	if (p == -1)
		return (errno);
	if (psa.error != 0)
		/* Failed; ready to reap */
		_waitpid(p, NULL, WNOHANG);
	else if (pid != NULL)
		/* exec succeeded */
		*pid = p;
	return (psa.error);
}
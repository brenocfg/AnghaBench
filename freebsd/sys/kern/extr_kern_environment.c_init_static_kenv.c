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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dynamic_kenv ; 
 char* kern_envp ; 
 char* kern_getenv (char*) ; 
 size_t md_env_len ; 
 scalar_t__ md_env_pos ; 
 char* md_envp ; 
 char* static_env ; 
 char* static_hints ; 
 scalar_t__ strcmp (char*,char*) ; 

void
init_static_kenv(char *buf, size_t len)
{
	char *eval;

	KASSERT(!dynamic_kenv, ("kenv: dynamic_kenv already initialized"));
	/*
	 * Suitably sized means it must be able to hold at least one empty
	 * variable, otherwise things go belly up if a kern_getenv call is
	 * made without a prior call to kern_setenv as we have a malformed
	 * environment.
	 */
	KASSERT(len == 0 || len >= 2,
	    ("kenv: static env must be initialized or suitably sized"));
	KASSERT(len == 0 || (*buf == '\0' && *(buf + 1) == '\0'),
	    ("kenv: sized buffer must be initially empty"));

	/*
	 * We may be called twice, with the second call needed to relocate
	 * md_envp after enabling paging.  md_envp is then garbage if it is
	 * not null and the relocation will move it.  Discard it so as to
	 * not crash using its old value in our first call to kern_getenv().
	 *
	 * The second call gives the same environment as the first except
	 * in silly configurations where the static env disables itself.
	 *
	 * Other env calls don't handle possibly-garbage pointers, so must
	 * not be made between enabling paging and calling here.
	 */
	md_envp = NULL;
	md_env_len = 0;
	md_env_pos = 0;

	/*
	 * Give the static environment a chance to disable the loader(8)
	 * environment first.  This is done with loader_env.disabled=1.
	 *
	 * static_env and static_hints may both be disabled, but in slightly
	 * different ways.  For static_env, we just don't setup kern_envp and
	 * it's as if a static env wasn't even provided.  For static_hints,
	 * we effectively zero out the buffer to stop the rest of the kernel
	 * from being able to use it.
	 *
	 * We're intentionally setting this up so that static_hints.disabled may
	 * be specified in either the MD env or the static env. This keeps us
	 * consistent in our new world view.
	 *
	 * As a warning, the static environment may not be disabled in any way
	 * if the static environment has disabled the loader environment.
	 */
	kern_envp = static_env;
	eval = kern_getenv("loader_env.disabled");
	if (eval == NULL || strcmp(eval, "1") != 0) {
		md_envp = buf;
		md_env_len = len;
		md_env_pos = 0;

		eval = kern_getenv("static_env.disabled");
		if (eval != NULL && strcmp(eval, "1") == 0) {
			kern_envp[0] = '\0';
			kern_envp[1] = '\0';
		}
	}
	eval = kern_getenv("static_hints.disabled");
	if (eval != NULL && strcmp(eval, "1") == 0) {
		static_hints[0] = '\0';
		static_hints[1] = '\0';
	}
}
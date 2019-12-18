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
 int /*<<< orphan*/  _DYNAMIC ; 
 int /*<<< orphan*/  _init_tls () ; 
 void _mcleanup () ; 
 int /*<<< orphan*/  atexit (void (*) ()) ; 
 int /*<<< orphan*/  eprol ; 
 int /*<<< orphan*/  etext ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_argv (int,char**,char**) ; 
 int /*<<< orphan*/  handle_static_init (int,char**,char**) ; 
 int /*<<< orphan*/  main (int,char**,char**) ; 
 int /*<<< orphan*/  monstartup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_irelocs () ; 

void
_start(char **ap, void (*cleanup)(void))
{
	int argc;
	char **argv;
	char **env;

	argc = *(long *)(void *)ap;
	argv = ap + 1;
	env = ap + 2 + argc;
	handle_argv(argc, argv, env);

	if (&_DYNAMIC != NULL) {
		atexit(cleanup);
	} else {
		process_irelocs();
		_init_tls();
	}

#ifdef GCRT
	atexit(_mcleanup);
	monstartup(&eprol, &etext);
__asm__("eprol:");
#endif

	handle_static_init(argc, argv, env);
	exit(main(argc, argv, env));
}
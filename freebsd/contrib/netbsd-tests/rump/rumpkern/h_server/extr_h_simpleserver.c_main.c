#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* dofun ) (char*) ;int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUMP_DAEMONIZE_SUCCESS ; 
 unsigned int __arraycount (TYPE_1__*) ; 
 TYPE_1__* actions ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  rump_daemonize_begin () ; 
 int /*<<< orphan*/  rump_daemonize_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_init () ; 
 int /*<<< orphan*/  rump_init_server (char*) ; 
 int /*<<< orphan*/  rump_schedule () ; 
 int /*<<< orphan*/  rump_unschedule () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

int
main(int argc, char *argv[])
{
	unsigned i;
	bool match;

	if (argc < 2)
		exit(1);

	NOFAIL(rump_daemonize_begin());
	NOFAIL(rump_init());
	NOFAIL(rump_init_server(argv[1]));
	NOFAIL(rump_daemonize_done(RUMP_DAEMONIZE_SUCCESS));

	if (argc > 2) {
		char *arg = NULL;

		if (argc == 4)
			arg = argv[3];

		for (i = 0; i < __arraycount(actions); i++) {
			if (strcmp(actions[i].str, argv[2]) == 0) {
				rump_schedule();
				actions[i].dofun(arg);
				rump_unschedule();
				match = true;
			}
		}

		if (!match) {
			exit(1);
		}
		pause();
	} else {
		for (;;)
			pause();
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttyent {char* ty_name; int ty_status; scalar_t__ ty_getty; } ;
typedef  int /*<<< orphan*/  state_func_t ;
struct TYPE_5__ {int se_flags; int /*<<< orphan*/  se_process; struct TYPE_5__* se_next; scalar_t__ se_started; scalar_t__ se_nspace; scalar_t__ se_type; scalar_t__ se_window; scalar_t__ se_getty; scalar_t__ se_device; } ;
typedef  TYPE_1__ session_t ;
typedef  int /*<<< orphan*/  _PATH_DEV ;

/* Variables and functions */
 int SE_PRESENT ; 
 int SE_SHUTDOWN ; 
 int /*<<< orphan*/  SIGHUP ; 
 int TTY_ON ; 
 int /*<<< orphan*/  endttyent () ; 
 int /*<<< orphan*/  free (char*) ; 
 struct ttyent* getttyent () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_user ; 
 int /*<<< orphan*/  new_session (TYPE_1__*,struct ttyent*) ; 
 TYPE_1__* sessions ; 
 scalar_t__ setupargv (TYPE_1__*,struct ttyent*) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 char* strdup (scalar_t__) ; 
 int /*<<< orphan*/  warning (char*,scalar_t__) ; 

__attribute__((used)) static state_func_t
clean_ttys(void)
{
	session_t *sp, *sprev;
	struct ttyent *typ;
	int devlen;
	char *old_getty, *old_window, *old_type;

	/*
	 * mark all sessions for death, (!SE_PRESENT)
	 * as we find or create new ones they'll be marked as keepers,
	 * we'll later nuke all the ones not found in /etc/ttys
	 */
	for (sp = sessions; sp != NULL; sp = sp->se_next)
		sp->se_flags &= ~SE_PRESENT;

	devlen = sizeof(_PATH_DEV) - 1;
	while ((typ = getttyent()) != NULL) {
		for (sprev = 0, sp = sessions; sp; sprev = sp, sp = sp->se_next)
			if (strcmp(typ->ty_name, sp->se_device + devlen) == 0)
				break;

		if (sp) {
			/* we want this one to live */
			sp->se_flags |= SE_PRESENT;
			if ((typ->ty_status & TTY_ON) == 0 ||
			    typ->ty_getty == 0) {
				sp->se_flags |= SE_SHUTDOWN;
				kill(sp->se_process, SIGHUP);
				continue;
			}
			sp->se_flags &= ~SE_SHUTDOWN;
			old_getty = sp->se_getty ? strdup(sp->se_getty) : 0;
			old_window = sp->se_window ? strdup(sp->se_window) : 0;
			old_type = sp->se_type ? strdup(sp->se_type) : 0;
			if (setupargv(sp, typ) == 0) {
				warning("can't parse getty for port %s",
					sp->se_device);
				sp->se_flags |= SE_SHUTDOWN;
				kill(sp->se_process, SIGHUP);
			}
			else if (   !old_getty
				 || (!old_type && sp->se_type)
				 || (old_type && !sp->se_type)
				 || (!old_window && sp->se_window)
				 || (old_window && !sp->se_window)
				 || (strcmp(old_getty, sp->se_getty) != 0)
				 || (old_window && strcmp(old_window, sp->se_window) != 0)
				 || (old_type && strcmp(old_type, sp->se_type) != 0)
				) {
				/* Don't set SE_SHUTDOWN here */
				sp->se_nspace = 0;
				sp->se_started = 0;
				kill(sp->se_process, SIGHUP);
			}
			if (old_getty)
				free(old_getty);
			if (old_window)
				free(old_window);
			if (old_type)
				free(old_type);
			continue;
		}

		new_session(sprev, typ);
	}

	endttyent();

	/*
	 * sweep through and kill all deleted sessions
	 * ones who's /etc/ttys line was deleted (SE_PRESENT unset)
	 */
	for (sp = sessions; sp != NULL; sp = sp->se_next) {
		if ((sp->se_flags & SE_PRESENT) == 0) {
			sp->se_flags |= SE_SHUTDOWN;
			kill(sp->se_process, SIGHUP);
		}
	}

	return (state_func_t) multi_user;
}
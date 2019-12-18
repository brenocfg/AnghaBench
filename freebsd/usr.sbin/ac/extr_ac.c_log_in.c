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
struct utmpx_entry {int /*<<< orphan*/  time; int /*<<< orphan*/  line; int /*<<< orphan*/  id; int /*<<< orphan*/  user; } ;
struct utmpx {char* ut_host; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_user; } ;

/* Variables and functions */
 int AC_T ; 
 int /*<<< orphan*/  Console ; 
 int /*<<< orphan*/  CurUtmpx ; 
 int /*<<< orphan*/  FirstTime ; 
 int Flags ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct utmpx_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_tty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct utmpx_entry* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 scalar_t__ on_console () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
log_in(struct utmpx *up)
{
	struct utmpx_entry *lp;

	/*
	 * this could be a login. if we're not dealing with
	 * the console name, say it is.
	 *
	 * If we are, and if ut_host==":0.0" we know that it
	 * isn't a real login. _But_ if we have not yet recorded
	 * someone being logged in on Console - due to the wtmp
	 * file starting after they logged in, we'll pretend they
	 * logged in, at the start of the wtmp file.
	 */

#ifdef CONSOLE_TTY
	if (up->ut_host[0] == ':') {
		/*
		 * SunOS 4.0.2 does not treat ":0.0" as special but we
		 * do.
		 */
		if (on_console())
			return;
		/*
		 * ok, no recorded login, so they were here when wtmp
		 * started!  Adjust ut_time!
		 */
		up->ut_tv = FirstTime;
		/*
		 * this allows us to pick the right logout
		 */
		strlcpy(up->ut_line, Console, sizeof(up->ut_line));
	}
#endif
	/*
	 * If we are doing specified ttys only, we ignore
	 * anything else.
	 */
	if (Flags & AC_T && !do_tty(up->ut_line))
		return;

	/*
	 * go ahead and log them in
	 */
	if ((lp = malloc(sizeof(*lp))) == NULL)
		errx(1, "malloc failed");
	SLIST_INSERT_HEAD(&CurUtmpx, lp, next);
	strlcpy(lp->user, up->ut_user, sizeof(lp->user));
	memcpy(lp->id, up->ut_id, sizeof(lp->id));
#ifdef CONSOLE_TTY
	memcpy(lp->line, up->ut_line, sizeof(lp->line));
#endif
	lp->time = up->ut_tv;
}
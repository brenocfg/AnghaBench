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
struct session {int dummy; } ;

/* Variables and functions */
 struct session* LIST_END (int /*<<< orphan*/ *) ; 
 struct session* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct session* LIST_NEXT (struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  end_session (struct session*) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sessions ; 

void
exit_daemon(void)
{
	struct session *s, *next;

	for (s = LIST_FIRST(&sessions); s != LIST_END(&sessions); s = next) {
		next = LIST_NEXT(s, entry);
		end_session(s);
	}

	if (daemonize)
		closelog();

	exit(0);
}
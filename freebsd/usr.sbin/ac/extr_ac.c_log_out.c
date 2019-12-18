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
struct utmpx_entry {int /*<<< orphan*/  user; int /*<<< orphan*/  time; int /*<<< orphan*/  id; } ;
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_id; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 scalar_t__ BOOT_TIME ; 
 int /*<<< orphan*/  CurUtmpx ; 
 scalar_t__ DEAD_PROCESS ; 
 scalar_t__ SHUTDOWN_TIME ; 
 struct utmpx_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct utmpx_entry* SLIST_NEXT (struct utmpx_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_AFTER (struct utmpx_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct utmpx_entry*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  timersub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  update_user (int /*<<< orphan*/ ,struct timeval) ; 

__attribute__((used)) static void
log_out(const struct utmpx *up)
{
	struct utmpx_entry *lp, *lp2, *tlp;
	struct timeval secs;

	for (lp = SLIST_FIRST(&CurUtmpx), lp2 = NULL; lp != NULL;)
		if (up->ut_type == BOOT_TIME || up->ut_type == SHUTDOWN_TIME ||
		    (up->ut_type == DEAD_PROCESS &&
		    memcmp(lp->id, up->ut_id, sizeof(up->ut_id)) == 0)) {
			timersub(&up->ut_tv, &lp->time, &secs);
			update_user(lp->user, secs);
			/*
			 * now lose it
			 */
			tlp = lp;
			lp = SLIST_NEXT(lp, next);
			if (lp2 == NULL)
				SLIST_REMOVE_HEAD(&CurUtmpx, next);
			else
				SLIST_REMOVE_AFTER(lp2, next);
			free(tlp);
		} else {
			lp2 = lp;
			lp = SLIST_NEXT(lp, next);
		}
}
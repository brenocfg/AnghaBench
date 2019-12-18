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
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int kevent (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int wait_for_dir_kq ; 

void
wait_for_dir(void)
{
#ifdef HAVE_KQUEUE
	struct kevent ev;
#endif

	if (wait_for_dir_kq == -1) {
		sleep(1);
		return;
	}

#ifdef HAVE_KQUEUE
	PJDLOG_ASSERT(wait_for_dir_kq != -1);

	if (kevent(wait_for_dir_kq, NULL, 0, &ev, 1, NULL) == -1) {
		pjdlog_errno(LOG_WARNING, "kevent() failed");
		sleep(1);
	}
#endif
}
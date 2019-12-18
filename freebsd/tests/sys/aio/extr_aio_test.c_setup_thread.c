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
struct sigevent {int /*<<< orphan*/ * sigev_notify_attributes; int /*<<< orphan*/  sigev_notify_function; int /*<<< orphan*/  sigev_notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGEV_THREAD ; 
 int /*<<< orphan*/  completions ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr_handler ; 

__attribute__((used)) static struct sigevent*
setup_thread(void)
{
	static struct sigevent sev;

	ATF_REQUIRE_EQ(0, sem_init(&completions, false, 0));
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = thr_handler;
	sev.sigev_notify_attributes = NULL;
	return (&sev);
}
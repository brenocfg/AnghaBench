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
struct cond_wait {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOCK_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_COND_SIGNAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wake_one_timeout(evutil_socket_t fd, short what, void *arg)
{
	struct cond_wait *cw = arg;
	EVLOCK_LOCK(cw->lock, 0);
	EVTHREAD_COND_SIGNAL(cw->cond);
	EVLOCK_UNLOCK(cw->lock, 0);
}
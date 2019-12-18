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
typedef  scalar_t__ u_int ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INSIST (int) ; 
 int EV_PERSIST ; 
 int EV_TIMEOUT ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/ * ev_worker_timeout ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * event_new (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_timeout ; 

void
intres_timeout_req(
	u_int	seconds		/* 0 cancels */
	)
{
	struct timeval	tv_to;

	if (NULL == ev_worker_timeout) {
		ev_worker_timeout = event_new(base, -1,
					      EV_TIMEOUT | EV_PERSIST,
					      &worker_timeout, NULL);
		DEBUG_INSIST(NULL != ev_worker_timeout);
	} else {
		event_del(ev_worker_timeout);
	}
	if (0 == seconds)
		return;
	tv_to.tv_sec = seconds;
	tv_to.tv_usec = 0;
	event_add(ev_worker_timeout, &tv_to);
}
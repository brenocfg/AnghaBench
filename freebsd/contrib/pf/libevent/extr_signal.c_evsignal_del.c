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
struct sigaction {int dummy; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int EVENT_SIGNAL (struct event*) ; 
 scalar_t__ SIG_DFL ; 
 int sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 

int
evsignal_del(struct event *ev)
{
	int evsignal;

	evsignal = EVENT_SIGNAL(ev);

	return (sigaction(EVENT_SIGNAL(ev),(struct sigaction *)SIG_DFL, NULL));
}
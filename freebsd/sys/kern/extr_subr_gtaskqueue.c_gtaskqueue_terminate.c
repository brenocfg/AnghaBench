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
struct thread {int dummy; } ;
struct gtaskqueue {scalar_t__ tq_tcount; scalar_t__ tq_callouts; } ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_SLEEP (struct gtaskqueue*,struct thread**,char*) ; 
 int /*<<< orphan*/  wakeup (struct gtaskqueue*) ; 

__attribute__((used)) static void
gtaskqueue_terminate(struct thread **pp, struct gtaskqueue *tq)
{

	while (tq->tq_tcount > 0 || tq->tq_callouts > 0) {
		wakeup(tq);
		TQ_SLEEP(tq, pp, "gtq_destroy");
	}
}
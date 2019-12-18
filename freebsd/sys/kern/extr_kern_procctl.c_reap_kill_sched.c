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
struct reap_kill_tracker_head {int dummy; } ;
struct reap_kill_tracker {struct proc* parent; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct reap_kill_tracker_head*,struct reap_kill_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct reap_kill_tracker* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reap_kill_sched(struct reap_kill_tracker_head *tracker, struct proc *p2)
{
	struct reap_kill_tracker *t;

	t = malloc(sizeof(struct reap_kill_tracker), M_TEMP, M_WAITOK);
	t->parent = p2;
	TAILQ_INSERT_TAIL(tracker, t, link);
}
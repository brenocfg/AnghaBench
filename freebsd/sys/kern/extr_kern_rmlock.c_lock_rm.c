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
struct rmlock {int dummy; } ;
struct rm_priotracker {int dummy; } ;
struct lock_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rm_rlock (struct rmlock*,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_wlock (struct rmlock*) ; 

__attribute__((used)) static void
lock_rm(struct lock_object *lock, uintptr_t how)
{
	struct rmlock *rm;
	struct rm_priotracker *tracker;

	rm = (struct rmlock *)lock;
	if (how == 0)
		rm_wlock(rm);
	else {
		tracker = (struct rm_priotracker *)how;
		rm_rlock(rm, tracker);
	}
}
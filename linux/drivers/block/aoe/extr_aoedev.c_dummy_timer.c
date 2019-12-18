#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct aoedev {int flags; TYPE_1__ timer; } ;

/* Variables and functions */
 int DEVFL_TKILL ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct aoedev* from_timer (struct aoedev*,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void
dummy_timer(struct timer_list *t)
{
	struct aoedev *d;

	d = from_timer(d, t, timer);
	if (d->flags & DEVFL_TKILL)
		return;
	d->timer.expires = jiffies + HZ;
	add_timer(&d->timer);
}
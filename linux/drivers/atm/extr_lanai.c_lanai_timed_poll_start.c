#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct lanai_dev {TYPE_1__ timer; } ;

/* Variables and functions */
 scalar_t__ LANAI_POLL_PERIOD ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lanai_timed_poll ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lanai_timed_poll_start(struct lanai_dev *lanai)
{
	timer_setup(&lanai->timer, lanai_timed_poll, 0);
	lanai->timer.expires = jiffies + LANAI_POLL_PERIOD;
	add_timer(&lanai->timer);
}
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
struct timer_list {int dummy; } ;
struct push_switch {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  debounce ; 
 struct push_switch* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct push_switch* psw ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void switch_timer(struct timer_list *t)
{
	struct push_switch *psw = from_timer(psw, t, debounce);

	schedule_work(&psw->work);
}
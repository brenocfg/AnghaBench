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
struct timer_list {void (* function ) (unsigned long) ;unsigned long data; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_timer (struct timer_list*) ; 

void
setup_timer(struct timer_list *t, void (*function)(unsigned long), unsigned long data)
{
	t->function = function;
	t->data = data;
	init_timer(t);
}
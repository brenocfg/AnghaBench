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
struct waiting_tcp {scalar_t__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_timer_delete (scalar_t__) ; 
 int /*<<< orphan*/  free (struct waiting_tcp*) ; 

__attribute__((used)) static void
waiting_tcp_delete(struct waiting_tcp* w)
{
	if(!w) return;
	if(w->timer)
		comm_timer_delete(w->timer);
	free(w);
}
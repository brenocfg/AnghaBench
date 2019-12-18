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
struct tcpcb {scalar_t__ t_fb_ptr; } ;
struct tcp_rack {int t_timers_stopped; } ;

/* Variables and functions */

__attribute__((used)) static int
rack_stopall(struct tcpcb *tp)
{
	struct tcp_rack *rack;
	rack = (struct tcp_rack *)tp->t_fb_ptr;
	rack->t_timers_stopped = 1;
	return (0);
}
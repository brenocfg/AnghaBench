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
struct tcpcb {scalar_t__ rcv_nxt; scalar_t__ rcv_adv; int /*<<< orphan*/  rcv_wnd; } ;
struct socket {int /*<<< orphan*/  so_rcv; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  imax (scalar_t__,int) ; 
 scalar_t__ sbspace (int /*<<< orphan*/ *) ; 

void
ctf_calc_rwin(struct socket *so, struct tcpcb *tp)
{
	int32_t win;

	/*
	 * Calculate amount of space in receive window, and then do TCP
	 * input processing. Receive window is amount of space in rcv queue,
	 * but not less than advertised window.
	 */
	win = sbspace(&so->so_rcv);
	if (win < 0)
		win = 0;
	tp->rcv_wnd = imax(win, (int)(tp->rcv_adv - tp->rcv_nxt));
}
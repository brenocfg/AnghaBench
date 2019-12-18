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
struct tcpcb {scalar_t__ t_softerror; scalar_t__ t_rxtshift; } ;
struct tcp_bbr {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

__attribute__((used)) static void
bbr_collapse_rtt(struct tcpcb *tp, struct tcp_bbr *bbr, int32_t rtt)
{
	/*
	 * Collapse timeout back the cum-ack moved.
	 */
	tp->t_rxtshift = 0;
	tp->t_softerror = 0;
}
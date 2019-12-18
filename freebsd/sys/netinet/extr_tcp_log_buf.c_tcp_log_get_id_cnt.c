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
typedef  int /*<<< orphan*/  u_int ;
struct tcpcb {TYPE_1__* t_lib; int /*<<< orphan*/  t_inpcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  tlb_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 

u_int
tcp_log_get_id_cnt(struct tcpcb *tp)
{

	INP_WLOCK_ASSERT(tp->t_inpcb);
	return ((tp->t_lib == NULL) ? 0 : tp->t_lib->tlb_refcnt);
}
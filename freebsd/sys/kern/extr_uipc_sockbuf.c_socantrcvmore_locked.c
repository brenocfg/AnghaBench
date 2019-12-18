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
struct TYPE_3__ {int /*<<< orphan*/  sb_state; } ;
struct socket {TYPE_1__ so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  SBS_CANTRCVMORE ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCKBUF_MTX (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup_locked (struct socket*) ; 

void
socantrcvmore_locked(struct socket *so)
{

	SOCKBUF_LOCK_ASSERT(&so->so_rcv);

	so->so_rcv.sb_state |= SBS_CANTRCVMORE;
	sorwakeup_locked(so);
	mtx_assert(SOCKBUF_MTX(&so->so_rcv), MA_NOTOWNED);
}
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
struct socket {int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_MTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socantrcvmore_locked (struct socket*) ; 

void
socantrcvmore(struct socket *so)
{

	SOCKBUF_LOCK(&so->so_rcv);
	socantrcvmore_locked(so);
	mtx_assert(SOCKBUF_MTX(&so->so_rcv), MA_NOTOWNED);
}
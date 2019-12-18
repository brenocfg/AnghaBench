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
struct unpcb {int /*<<< orphan*/  unp_gcflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_mb; } ;
struct socket {TYPE_1__ so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  UNPGC_IGNORE_RIGHTS ; 
 int /*<<< orphan*/  UNP_LINK_WLOCK () ; 
 int /*<<< orphan*/  UNP_LINK_WUNLOCK () ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_dispose_mbuf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unp_dispose(struct socket *so)
{
	struct unpcb *unp;

	unp = sotounpcb(so);
	UNP_LINK_WLOCK();
	unp->unp_gcflag |= UNPGC_IGNORE_RIGHTS;
	UNP_LINK_WUNLOCK();
	if (!SOLISTENING(so))
		unp_dispose_mbuf(so->so_rcv.sb_mb);
}
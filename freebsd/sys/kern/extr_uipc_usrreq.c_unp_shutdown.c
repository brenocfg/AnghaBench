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
struct unpcb {struct socket* unp_socket; struct unpcb* unp_conn; } ;
struct socket {scalar_t__ so_type; } ;

/* Variables and functions */
 scalar_t__ SOCK_SEQPACKET ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  UNP_PCB_LOCK_ASSERT (struct unpcb*) ; 
 int /*<<< orphan*/  socantrcvmore (struct socket*) ; 

__attribute__((used)) static void
unp_shutdown(struct unpcb *unp)
{
	struct unpcb *unp2;
	struct socket *so;

	UNP_PCB_LOCK_ASSERT(unp);

	unp2 = unp->unp_conn;
	if ((unp->unp_socket->so_type == SOCK_STREAM ||
	    (unp->unp_socket->so_type == SOCK_SEQPACKET)) && unp2 != NULL) {
		so = unp2->unp_socket;
		if (so != NULL)
			socantrcvmore(so);
	}
}
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
struct socket {scalar_t__ so_pcb; } ;
struct ngpcb {int type; struct socket* ng_socket; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ngpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PCB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct ngpcb* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngpdg_recvspace ; 
 int /*<<< orphan*/  ngpdg_sendspace ; 
 int /*<<< orphan*/  ngsocketlist_mtx ; 
 int /*<<< orphan*/  ngsocklist ; 
 int /*<<< orphan*/  socks ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_attach_common(struct socket *so, int type)
{
	struct ngpcb *pcbp;
	int error;

	/* Standard socket setup stuff. */
	error = soreserve(so, ngpdg_sendspace, ngpdg_recvspace);
	if (error)
		return (error);

	/* Allocate the pcb. */
	pcbp = malloc(sizeof(struct ngpcb), M_PCB, M_WAITOK | M_ZERO);
	pcbp->type = type;

	/* Link the pcb and the socket. */
	so->so_pcb = (caddr_t)pcbp;
	pcbp->ng_socket = so;

	/* Add the socket to linked list */
	mtx_lock(&ngsocketlist_mtx);
	LIST_INSERT_HEAD(&ngsocklist, pcbp, socks);
	mtx_unlock(&ngsocketlist_mtx);
	return (0);
}
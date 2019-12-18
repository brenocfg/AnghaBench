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
struct socket {struct rawcb* so_pcb; } ;
struct rawcb {struct socket* rcb_socket; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct rawcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PCB ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rawcb_mtx ; 

void
raw_detach(struct rawcb *rp)
{
	struct socket *so = rp->rcb_socket;

	KASSERT(so->so_pcb == rp, ("raw_detach: so_pcb != rp"));

	so->so_pcb = NULL;
	mtx_lock(&rawcb_mtx);
	LIST_REMOVE(rp, list);
	mtx_unlock(&rawcb_mtx);
	free((caddr_t)(rp), M_PCB);
}
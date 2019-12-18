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
struct ntb_transport_ctx {scalar_t__ qp_bitmap; int mw_count; struct ntb_transport_child* mw_vec; struct ntb_transport_child* qp_vec; int /*<<< orphan*/  link_watchdog; int /*<<< orphan*/  link_work; int /*<<< orphan*/  link_cleanup; struct ntb_transport_child* child; } ;
struct ntb_transport_child {int /*<<< orphan*/  dev; struct ntb_transport_child* next; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NTB_T ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_transport_ctx* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ntb_transport_child*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_clear_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_free_mw (struct ntb_transport_ctx*,int) ; 
 int /*<<< orphan*/  ntb_link_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_transport_link_cleanup (struct ntb_transport_ctx*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static int
ntb_transport_detach(device_t dev)
{
	struct ntb_transport_ctx *nt = device_get_softc(dev);
	struct ntb_transport_child **cpp = &nt->child;
	struct ntb_transport_child *nc;
	int error = 0, i;

	while ((nc = *cpp) != NULL) {
		*cpp = (*cpp)->next;
		error = device_delete_child(dev, nc->dev);
		if (error)
			break;
		free(nc, M_DEVBUF);
	}
	KASSERT(nt->qp_bitmap == 0,
	    ("Some queues not freed on detach (%jx)", nt->qp_bitmap));

	ntb_transport_link_cleanup(nt);
	taskqueue_drain(taskqueue_swi, &nt->link_cleanup);
	callout_drain(&nt->link_work);
	callout_drain(&nt->link_watchdog);

	ntb_link_disable(dev);
	ntb_clear_ctx(dev);

	for (i = 0; i < nt->mw_count; i++)
		ntb_free_mw(nt, i);

	free(nt->qp_vec, M_NTB_T);
	free(nt->mw_vec, M_NTB_T);
	return (0);
}
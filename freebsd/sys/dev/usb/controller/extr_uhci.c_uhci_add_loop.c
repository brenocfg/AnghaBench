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
struct TYPE_3__ {int sc_loops; struct uhci_qh* sc_reclaim_qh_p; struct uhci_qh* sc_last_qh_p; } ;
typedef  TYPE_1__ uhci_softc_t ;
struct uhci_qh {int /*<<< orphan*/  page_cache; int /*<<< orphan*/  qh_self; int /*<<< orphan*/  qh_h_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 scalar_t__ uhcinoloop ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhci_add_loop(uhci_softc_t *sc)
{
	struct uhci_qh *qh_lst;
	struct uhci_qh *qh_rec;

#ifdef USB_DEBUG
	if (uhcinoloop) {
		return;
	}
#endif
	if (++(sc->sc_loops) == 1) {
		DPRINTFN(6, "add\n");

		qh_lst = sc->sc_last_qh_p;
		qh_rec = sc->sc_reclaim_qh_p;

		/* NOTE: we don't loop back the soft pointer */

		qh_lst->qh_h_next = qh_rec->qh_self;
		usb_pc_cpu_flush(qh_lst->page_cache);
	}
}
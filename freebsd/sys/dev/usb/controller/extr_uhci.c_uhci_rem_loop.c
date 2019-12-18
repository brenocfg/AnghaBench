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
struct TYPE_3__ {scalar_t__ sc_loops; struct uhci_qh* sc_last_qh_p; } ;
typedef  TYPE_1__ uhci_softc_t ;
struct uhci_qh {int /*<<< orphan*/  page_cache; int /*<<< orphan*/  qh_h_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  UHCI_PTR_T ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 scalar_t__ uhcinoloop ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhci_rem_loop(uhci_softc_t *sc)
{
	struct uhci_qh *qh_lst;

#ifdef USB_DEBUG
	if (uhcinoloop) {
		return;
	}
#endif
	if (--(sc->sc_loops) == 0) {
		DPRINTFN(6, "remove\n");

		qh_lst = sc->sc_last_qh_p;
		qh_lst->qh_h_next = htole32(UHCI_PTR_T);
		usb_pc_cpu_flush(qh_lst->page_cache);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  page_cache; int /*<<< orphan*/  ed_self; int /*<<< orphan*/  ed_next; struct TYPE_5__* next; struct TYPE_5__* prev; scalar_t__ ed_tailp; } ;
typedef  TYPE_1__ ohci_ed_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ohci_ed_t *
_ohci_append_qh(ohci_ed_t *sed, ohci_ed_t *last)
{
	DPRINTFN(11, "%p to %p\n", sed, last);

	if (sed->prev != NULL) {
		/* should not happen */
		DPRINTFN(0, "ED already linked!\n");
		return (last);
	}
	/* (sc->sc_bus.bus_mtx) must be locked */

	sed->next = last->next;
	sed->ed_next = last->ed_next;
	sed->ed_tailp = 0;

	sed->prev = last;

	usb_pc_cpu_flush(sed->page_cache);

	/*
	 * the last->next->prev is never followed: sed->next->prev = sed;
	 */

	last->next = sed;
	last->ed_next = sed->ed_self;

	usb_pc_cpu_flush(last->page_cache);

	return (sed);
}
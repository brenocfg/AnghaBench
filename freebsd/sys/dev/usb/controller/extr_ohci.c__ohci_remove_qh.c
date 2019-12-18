#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  page_cache; struct TYPE_9__* prev; TYPE_1__* next; int /*<<< orphan*/  ed_next; } ;
typedef  TYPE_2__ ohci_ed_t ;
struct TYPE_8__ {int /*<<< orphan*/  page_cache; TYPE_2__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ohci_ed_t *
_ohci_remove_qh(ohci_ed_t *sed, ohci_ed_t *last)
{
	DPRINTFN(11, "%p from %p\n", sed, last);

	/* (sc->sc_bus.bus_mtx) must be locked */

	/* only remove if not removed from a queue */
	if (sed->prev) {

		sed->prev->next = sed->next;
		sed->prev->ed_next = sed->ed_next;

		usb_pc_cpu_flush(sed->prev->page_cache);

		if (sed->next) {
			sed->next->prev = sed->prev;
			usb_pc_cpu_flush(sed->next->page_cache);
		}
		last = ((last == sed) ? sed->prev : last);

		sed->prev = 0;

		usb_pc_cpu_flush(sed->page_cache);
	}
	return (last);
}
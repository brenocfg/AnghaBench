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
struct xbd_softc {int /*<<< orphan*/  xen_intr_handle; int /*<<< orphan*/  xbd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xen_intr_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void 
xbd_flush_requests(struct xbd_softc *sc)
{
	int notify;

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&sc->xbd_ring, notify);

	if (notify)
		xen_intr_signal(sc->xen_intr_handle);
}
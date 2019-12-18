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
struct l2_packet_data {int /*<<< orphan*/  rx_written; int /*<<< orphan*/  rx_overlapped; int /*<<< orphan*/  rx_avail; } ;
struct TYPE_2__ {int refcount; int /*<<< orphan*/  rx_processed; struct l2_packet_data** l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetOverlappedResult (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_ndis_get_ndisuio_handle () ; 
 TYPE_1__* l2_ndisuio_global ; 
 int /*<<< orphan*/  l2_packet_callback (struct l2_packet_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void l2_packet_rx_event(void *eloop_data, void *user_data)
{
	struct l2_packet_data *l2 = eloop_data;

	if (l2_ndisuio_global)
		l2 = l2_ndisuio_global->l2[l2_ndisuio_global->refcount - 1];

	ResetEvent(l2->rx_avail);

#ifndef _WIN32_WCE
	if (!GetOverlappedResult(driver_ndis_get_ndisuio_handle(),
				 &l2->rx_overlapped, &l2->rx_written, FALSE)) {
		wpa_printf(MSG_DEBUG, "L2(NDISUIO): GetOverlappedResult "
			   "failed: %d", (int) GetLastError());
		return;
	}
#endif /* _WIN32_WCE */

	l2_packet_callback(l2);

#ifdef _WIN32_WCE
	SetEvent(l2_ndisuio_global->rx_processed);
#endif /* _WIN32_WCE */
}
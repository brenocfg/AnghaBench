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
struct l2_packet_data {size_t refcount; int /*<<< orphan*/  rx_avail; int /*<<< orphan*/  rx_processed; int /*<<< orphan*/  ready_for_read; int /*<<< orphan*/  stop_request; int /*<<< orphan*/  rx_thread; int /*<<< orphan*/  first_proto; int /*<<< orphan*/ ** l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CancelIo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IOCTL_CANCEL_READ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_ndis_get_ndisuio_handle () ; 
 int /*<<< orphan*/  eloop_unregister_event (int /*<<< orphan*/ ,int) ; 
 struct l2_packet_data* l2_ndisuio_global ; 
 int /*<<< orphan*/  l2_ndisuio_set_ether_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct l2_packet_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

void l2_packet_deinit(struct l2_packet_data *l2)
{
	if (l2 == NULL)
		return;

	if (l2_ndisuio_global) {
		l2_ndisuio_global->refcount--;
		l2_ndisuio_global->l2[l2_ndisuio_global->refcount] = NULL;
		if (l2_ndisuio_global->refcount) {
			wpa_printf(MSG_DEBUG, "L2(NDISUIO): restore filtering "
				   "ethertype to %04x",
				   l2_ndisuio_global->first_proto);
			l2_ndisuio_set_ether_type(
				l2_ndisuio_global->first_proto);
			return;
		}

#ifdef _WIN32_WCE
		wpa_printf(MSG_DEBUG, "L2(NDISUIO): Waiting for RX thread to "
			   "stop");
		SetEvent(l2_ndisuio_global->stop_request);
		/*
		 * Cancel pending ReadFile() in the RX thread (if we were still
		 * connected at this point).
		 */
		if (!DeviceIoControl(driver_ndis_get_ndisuio_handle(),
				     IOCTL_CANCEL_READ, NULL, 0, NULL, 0, NULL,
				     NULL)) {
			wpa_printf(MSG_DEBUG, "L2(NDISUIO): IOCTL_CANCEL_READ "
				   "failed: %d", (int) GetLastError());
			/* RX thread will exit blocking ReadFile once NDISUIO
			 * notices that the adapter is disconnected. */
		}
		WaitForSingleObject(l2_ndisuio_global->rx_thread, INFINITE);
		wpa_printf(MSG_DEBUG, "L2(NDISUIO): RX thread exited");
		CloseHandle(l2_ndisuio_global->rx_thread);
		CloseHandle(l2_ndisuio_global->stop_request);
		CloseHandle(l2_ndisuio_global->ready_for_read);
		CloseHandle(l2_ndisuio_global->rx_processed);
#endif /* _WIN32_WCE */

		os_free(l2_ndisuio_global);
		l2_ndisuio_global = NULL;
	}

#ifndef _WIN32_WCE
	CancelIo(driver_ndis_get_ndisuio_handle());
#endif /* _WIN32_WCE */

	eloop_unregister_event(l2->rx_avail, sizeof(l2->rx_avail));
	CloseHandle(l2->rx_avail);
	os_free(l2);
}
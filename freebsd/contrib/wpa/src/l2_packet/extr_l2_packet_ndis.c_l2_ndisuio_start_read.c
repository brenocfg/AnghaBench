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
struct TYPE_3__ {int /*<<< orphan*/  hEvent; } ;
struct l2_packet_data {TYPE_1__ rx_overlapped; int /*<<< orphan*/  rx_written; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  rx_avail; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  driver_ndis_get_ndisuio_handle () ; 
 int /*<<< orphan*/  l2_packet_callback (struct l2_packet_data*) ; 
 int /*<<< orphan*/  os_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int l2_ndisuio_start_read(struct l2_packet_data *l2, int recursive)
{
	os_memset(&l2->rx_overlapped, 0, sizeof(l2->rx_overlapped));
	l2->rx_overlapped.hEvent = l2->rx_avail;
	if (!ReadFile(driver_ndis_get_ndisuio_handle(), l2->rx_buf,
		      sizeof(l2->rx_buf), &l2->rx_written, &l2->rx_overlapped))
	{
		DWORD err = GetLastError();
		if (err != ERROR_IO_PENDING) {
			wpa_printf(MSG_DEBUG, "L2(NDISUIO): ReadFile failed: "
				   "%d", (int) err);
			return -1;
		}
		/*
		 * Once read is completed, l2_packet_rx_event() will be
		 * called.
		 */
	} else {
		wpa_printf(MSG_DEBUG, "L2(NDISUIO): ReadFile returned data "
			   "without wait for completion");
		if (!recursive)
			l2_packet_callback(l2);
	}

	return 0;
}
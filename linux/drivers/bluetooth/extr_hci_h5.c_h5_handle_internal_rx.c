#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hci_uart {TYPE_2__* hdev; struct h5* priv; } ;
struct h5 {scalar_t__ state; unsigned char tx_win; void* sleep; TYPE_1__* rx_skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {unsigned char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 scalar_t__ H5_ACTIVE ; 
 void* H5_AWAKE ; 
 int H5_HDR_LEN (unsigned char const*) ; 
 scalar_t__ H5_HDR_PKT_TYPE (unsigned char const*) ; 
 scalar_t__ H5_INITIALIZED ; 
 void* H5_SLEEPING ; 
 scalar_t__ HCI_3WIRE_LINK_PKT ; 
 unsigned char h5_cfg_field (struct h5*) ; 
 int /*<<< orphan*/  h5_link_control (struct hci_uart*,unsigned char const*,int) ; 
 int /*<<< orphan*/  h5_peer_reset (struct hci_uart*) ; 
 int /*<<< orphan*/  hci_uart_init_ready (struct hci_uart*) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,int) ; 

__attribute__((used)) static void h5_handle_internal_rx(struct hci_uart *hu)
{
	struct h5 *h5 = hu->priv;
	const unsigned char sync_req[] = { 0x01, 0x7e };
	const unsigned char sync_rsp[] = { 0x02, 0x7d };
	unsigned char conf_req[3] = { 0x03, 0xfc };
	const unsigned char conf_rsp[] = { 0x04, 0x7b };
	const unsigned char wakeup_req[] = { 0x05, 0xfa };
	const unsigned char woken_req[] = { 0x06, 0xf9 };
	const unsigned char sleep_req[] = { 0x07, 0x78 };
	const unsigned char *hdr = h5->rx_skb->data;
	const unsigned char *data = &h5->rx_skb->data[4];

	BT_DBG("%s", hu->hdev->name);

	if (H5_HDR_PKT_TYPE(hdr) != HCI_3WIRE_LINK_PKT)
		return;

	if (H5_HDR_LEN(hdr) < 2)
		return;

	conf_req[2] = h5_cfg_field(h5);

	if (memcmp(data, sync_req, 2) == 0) {
		if (h5->state == H5_ACTIVE)
			h5_peer_reset(hu);
		h5_link_control(hu, sync_rsp, 2);
	} else if (memcmp(data, sync_rsp, 2) == 0) {
		if (h5->state == H5_ACTIVE)
			h5_peer_reset(hu);
		h5->state = H5_INITIALIZED;
		h5_link_control(hu, conf_req, 3);
	} else if (memcmp(data, conf_req, 2) == 0) {
		h5_link_control(hu, conf_rsp, 2);
		h5_link_control(hu, conf_req, 3);
	} else if (memcmp(data, conf_rsp, 2) == 0) {
		if (H5_HDR_LEN(hdr) > 2)
			h5->tx_win = (data[2] & 0x07);
		BT_DBG("Three-wire init complete. tx_win %u", h5->tx_win);
		h5->state = H5_ACTIVE;
		hci_uart_init_ready(hu);
		return;
	} else if (memcmp(data, sleep_req, 2) == 0) {
		BT_DBG("Peer went to sleep");
		h5->sleep = H5_SLEEPING;
		return;
	} else if (memcmp(data, woken_req, 2) == 0) {
		BT_DBG("Peer woke up");
		h5->sleep = H5_AWAKE;
	} else if (memcmp(data, wakeup_req, 2) == 0) {
		BT_DBG("Peer requested wakeup");
		h5_link_control(hu, woken_req, 2);
		h5->sleep = H5_AWAKE;
	} else {
		BT_DBG("Link Control: 0x%02hhx 0x%02hhx", data[0], data[1]);
		return;
	}

	hci_uart_tx_wakeup(hu);
}
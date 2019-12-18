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
typedef  int /*<<< orphan*/  u8 ;
struct iapp_layer2_update {int ssap; int control; int* xid_info; scalar_t__ dsap; int /*<<< orphan*/  len; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;
struct iapp_data {int /*<<< orphan*/  packet_sock; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  host_to_be16 (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int /*<<< orphan*/ ,struct iapp_layer2_update*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iapp_send_layer2_update(struct iapp_data *iapp, u8 *addr)
{
	struct iapp_layer2_update msg;

	/* Send Level 2 Update Frame to update forwarding tables in layer 2
	 * bridge devices */

	/* 802.2 Type 1 Logical Link Control (LLC) Exchange Identifier (XID)
	 * Update response frame; IEEE Std 802.2-1998, 5.4.1.2.1 */

	os_memset(msg.da, 0xff, ETH_ALEN);
	os_memcpy(msg.sa, addr, ETH_ALEN);
	msg.len = host_to_be16(6);
	msg.dsap = 0; /* NULL DSAP address */
	msg.ssap = 0x01; /* NULL SSAP address, CR Bit: Response */
	msg.control = 0xaf; /* XID response lsb.1111F101.
			     * F=0 (no poll command; unsolicited frame) */
	msg.xid_info[0] = 0x81; /* XID format identifier */
	msg.xid_info[1] = 1; /* LLC types/classes: Type 1 LLC */
	msg.xid_info[2] = 1 << 1; /* XID sender's receive window size (RW)
				   * FIX: what is correct RW with 802.11? */

	if (send(iapp->packet_sock, &msg, sizeof(msg), 0) < 0)
		wpa_printf(MSG_INFO, "send[L2 Update]: %s", strerror(errno));
}
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
struct fw_device {int max_rec; scalar_t__ bc_implemented; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  node_id; int /*<<< orphan*/  irmc; struct fw_card* card; } ;
struct fw_card {int /*<<< orphan*/  broadcast_channel_allocated; } ;
typedef  int __be32 ;

/* Variables and functions */
 scalar_t__ BC_IMPLEMENTED ; 
 scalar_t__ BC_UNIMPLEMENTED ; 
 scalar_t__ BC_UNKNOWN ; 
 int BROADCAST_CHANNEL_INITIAL ; 
 int BROADCAST_CHANNEL_VALID ; 
 scalar_t__ CSR_BROADCAST_CHANNEL ; 
 scalar_t__ CSR_REGISTER_BASE ; 
#define  RCODE_ADDRESS_ERROR 129 
#define  RCODE_COMPLETE 128 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int cpu_to_be32 (int) ; 
 int fw_run_transaction (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int*,int) ; 

__attribute__((used)) static void set_broadcast_channel(struct fw_device *device, int generation)
{
	struct fw_card *card = device->card;
	__be32 data;
	int rcode;

	if (!card->broadcast_channel_allocated)
		return;

	/*
	 * The Broadcast_Channel Valid bit is required by nodes which want to
	 * transmit on this channel.  Such transmissions are practically
	 * exclusive to IP over 1394 (RFC 2734).  IP capable nodes are required
	 * to be IRM capable and have a max_rec of 8 or more.  We use this fact
	 * to narrow down to which nodes we send Broadcast_Channel updates.
	 */
	if (!device->irmc || device->max_rec < 8)
		return;

	/*
	 * Some 1394-1995 nodes crash if this 1394a-2000 register is written.
	 * Perform a read test first.
	 */
	if (device->bc_implemented == BC_UNKNOWN) {
		rcode = fw_run_transaction(card, TCODE_READ_QUADLET_REQUEST,
				device->node_id, generation, device->max_speed,
				CSR_REGISTER_BASE + CSR_BROADCAST_CHANNEL,
				&data, 4);
		switch (rcode) {
		case RCODE_COMPLETE:
			if (data & cpu_to_be32(1 << 31)) {
				device->bc_implemented = BC_IMPLEMENTED;
				break;
			}
			/* else, fall through - to case address error */
		case RCODE_ADDRESS_ERROR:
			device->bc_implemented = BC_UNIMPLEMENTED;
		}
	}

	if (device->bc_implemented == BC_IMPLEMENTED) {
		data = cpu_to_be32(BROADCAST_CHANNEL_INITIAL |
				   BROADCAST_CHANNEL_VALID);
		fw_run_transaction(card, TCODE_WRITE_QUADLET_REQUEST,
				device->node_id, generation, device->max_speed,
				CSR_REGISTER_BASE + CSR_BROADCAST_CHANNEL,
				&data, 4);
	}
}
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
struct fw_request {int dummy; } ;
struct fw_card {int split_timeout_hi; int split_timeout_lo; int broadcast_channel; int /*<<< orphan*/  maint_utility_register; int /*<<< orphan*/  lock; TYPE_1__* driver; int /*<<< orphan*/  priority_budget_implemented; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int (* read_csr ) (struct fw_card*,int) ;int /*<<< orphan*/  (* write_csr ) (struct fw_card*,int const,int) ;} ;

/* Variables and functions */
 int BROADCAST_CHANNEL_INITIAL ; 
 int BROADCAST_CHANNEL_VALID ; 
 int /*<<< orphan*/  BUG () ; 
#define  CSR_BANDWIDTH_AVAILABLE 143 
#define  CSR_BROADCAST_CHANNEL 142 
#define  CSR_BUSY_TIMEOUT 141 
#define  CSR_BUS_MANAGER_ID 140 
#define  CSR_BUS_TIME 139 
#define  CSR_CHANNELS_AVAILABLE_HI 138 
#define  CSR_CHANNELS_AVAILABLE_LO 137 
#define  CSR_CYCLE_TIME 136 
#define  CSR_MAINT_UTILITY 135 
#define  CSR_NODE_IDS 134 
#define  CSR_PRIORITY_BUDGET 133 
 unsigned long long CSR_REGISTER_BASE ; 
#define  CSR_RESET_START 132 
#define  CSR_SPLIT_TIMEOUT_HI 131 
#define  CSR_SPLIT_TIMEOUT_LO 130 
 int CSR_STATE_BIT_ABDICATE ; 
#define  CSR_STATE_CLEAR 129 
#define  CSR_STATE_SET 128 
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
 int TCODE_READ_QUADLET_REQUEST ; 
 int TCODE_WRITE_QUADLET_REQUEST ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct fw_card*,int) ; 
 int /*<<< orphan*/  stub2 (struct fw_card*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct fw_card*,int const,int) ; 
 int /*<<< orphan*/  update_split_timeout (struct fw_card*) ; 

__attribute__((used)) static void handle_registers(struct fw_card *card, struct fw_request *request,
		int tcode, int destination, int source, int generation,
		unsigned long long offset, void *payload, size_t length,
		void *callback_data)
{
	int reg = offset & ~CSR_REGISTER_BASE;
	__be32 *data = payload;
	int rcode = RCODE_COMPLETE;
	unsigned long flags;

	switch (reg) {
	case CSR_PRIORITY_BUDGET:
		if (!card->priority_budget_implemented) {
			rcode = RCODE_ADDRESS_ERROR;
			break;
		}
		/* else fall through */

	case CSR_NODE_IDS:
		/*
		 * per IEEE 1394-2008 8.3.22.3, not IEEE 1394.1-2004 3.2.8
		 * and 9.6, but interoperable with IEEE 1394.1-2004 bridges
		 */
		/* fall through */

	case CSR_STATE_CLEAR:
	case CSR_STATE_SET:
	case CSR_CYCLE_TIME:
	case CSR_BUS_TIME:
	case CSR_BUSY_TIMEOUT:
		if (tcode == TCODE_READ_QUADLET_REQUEST)
			*data = cpu_to_be32(card->driver->read_csr(card, reg));
		else if (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->driver->write_csr(card, reg, be32_to_cpu(*data));
		else
			rcode = RCODE_TYPE_ERROR;
		break;

	case CSR_RESET_START:
		if (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->driver->write_csr(card, CSR_STATE_CLEAR,
						CSR_STATE_BIT_ABDICATE);
		else
			rcode = RCODE_TYPE_ERROR;
		break;

	case CSR_SPLIT_TIMEOUT_HI:
		if (tcode == TCODE_READ_QUADLET_REQUEST) {
			*data = cpu_to_be32(card->split_timeout_hi);
		} else if (tcode == TCODE_WRITE_QUADLET_REQUEST) {
			spin_lock_irqsave(&card->lock, flags);
			card->split_timeout_hi = be32_to_cpu(*data) & 7;
			update_split_timeout(card);
			spin_unlock_irqrestore(&card->lock, flags);
		} else {
			rcode = RCODE_TYPE_ERROR;
		}
		break;

	case CSR_SPLIT_TIMEOUT_LO:
		if (tcode == TCODE_READ_QUADLET_REQUEST) {
			*data = cpu_to_be32(card->split_timeout_lo);
		} else if (tcode == TCODE_WRITE_QUADLET_REQUEST) {
			spin_lock_irqsave(&card->lock, flags);
			card->split_timeout_lo =
					be32_to_cpu(*data) & 0xfff80000;
			update_split_timeout(card);
			spin_unlock_irqrestore(&card->lock, flags);
		} else {
			rcode = RCODE_TYPE_ERROR;
		}
		break;

	case CSR_MAINT_UTILITY:
		if (tcode == TCODE_READ_QUADLET_REQUEST)
			*data = card->maint_utility_register;
		else if (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->maint_utility_register = *data;
		else
			rcode = RCODE_TYPE_ERROR;
		break;

	case CSR_BROADCAST_CHANNEL:
		if (tcode == TCODE_READ_QUADLET_REQUEST)
			*data = cpu_to_be32(card->broadcast_channel);
		else if (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->broadcast_channel =
			    (be32_to_cpu(*data) & BROADCAST_CHANNEL_VALID) |
			    BROADCAST_CHANNEL_INITIAL;
		else
			rcode = RCODE_TYPE_ERROR;
		break;

	case CSR_BUS_MANAGER_ID:
	case CSR_BANDWIDTH_AVAILABLE:
	case CSR_CHANNELS_AVAILABLE_HI:
	case CSR_CHANNELS_AVAILABLE_LO:
		/*
		 * FIXME: these are handled by the OHCI hardware and
		 * the stack never sees these request. If we add
		 * support for a new type of controller that doesn't
		 * handle this in hardware we need to deal with these
		 * transactions.
		 */
		BUG();
		break;

	default:
		rcode = RCODE_ADDRESS_ERROR;
		break;
	}

	fw_send_response(card, request, rcode);
}
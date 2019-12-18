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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct fw_card {int dummy; } ;
typedef  int __be32 ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
#define  RCODE_COMPLETE 129 
#define  RCODE_GENERATION 128 
 int /*<<< orphan*/  SCODE_100 ; 
 int /*<<< orphan*/  TCODE_LOCK_COMPARE_SWAP ; 
 int cpu_to_be32 (int) ; 
 int fw_run_transaction (struct fw_card*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int manage_channel(struct fw_card *card, int irm_id, int generation,
		u32 channels_mask, u64 offset, bool allocate)
{
	__be32 bit, all, old;
	__be32 data[2];
	int channel, ret = -EIO, retry = 5;

	old = all = allocate ? cpu_to_be32(~0) : 0;

	for (channel = 0; channel < 32; channel++) {
		if (!(channels_mask & 1 << channel))
			continue;

		ret = -EBUSY;

		bit = cpu_to_be32(1 << (31 - channel));
		if ((old & bit) != (all & bit))
			continue;

		data[0] = old;
		data[1] = old ^ bit;
		switch (fw_run_transaction(card, TCODE_LOCK_COMPARE_SWAP,
					   irm_id, generation, SCODE_100,
					   offset, data, 8)) {
		case RCODE_GENERATION:
			/* A generation change frees all channels. */
			return allocate ? -EAGAIN : channel;

		case RCODE_COMPLETE:
			if (data[0] == old)
				return channel;

			old = data[0];

			/* Is the IRM 1394a-2000 compliant? */
			if ((data[0] & bit) == (data[1] & bit))
				continue;

			/* fall through - It's a 1394-1995 IRM, retry. */
		default:
			if (retry) {
				retry--;
				channel--;
			} else {
				ret = -EIO;
			}
		}
	}

	return ret;
}
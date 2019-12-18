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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct vmbus_rxbr {int rxbr_dsize; int /*<<< orphan*/ * rxbr_data; } ;

/* Variables and functions */
 int VMBUS_BR_IDXINC (int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static __inline uint32_t
vmbus_rxbr_copyfrom(const struct vmbus_rxbr *rbr, uint32_t rindex,
    void *dst0, int cplen)
{
	uint8_t *dst = dst0;
	const uint8_t *br_data = rbr->rxbr_data;
	uint32_t br_dsize = rbr->rxbr_dsize;

	if (cplen > br_dsize - rindex) {
		uint32_t fraglen = br_dsize - rindex;

		/* Wrap-around detected. */
		memcpy(dst, br_data + rindex, fraglen);
		memcpy(dst + fraglen, br_data, cplen - fraglen);
	} else {
		memcpy(dst, br_data + rindex, cplen);
	}
	return VMBUS_BR_IDXINC(rindex, cplen, br_dsize);
}
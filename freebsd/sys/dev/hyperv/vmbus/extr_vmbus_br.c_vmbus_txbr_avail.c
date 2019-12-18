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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmbus_txbr {int /*<<< orphan*/  txbr_dsize; int /*<<< orphan*/  txbr_windex; int /*<<< orphan*/  txbr_rindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMBUS_BR_WAVAIL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint32_t
vmbus_txbr_avail(const struct vmbus_txbr *tbr)
{
	uint32_t rindex, windex;

	/* Get snapshot */
	rindex = tbr->txbr_rindex;
	windex = tbr->txbr_windex;

	return VMBUS_BR_WAVAIL(rindex, windex, tbr->txbr_dsize);
}
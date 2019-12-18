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
typedef  enum pasemi_dmachan_type { ____Placeholder_pasemi_dmachan_type } pasemi_dmachan_type ;

/* Variables and functions */
 int ENOSPC ; 
 int MAX_TXCH ; 
#define  TXCHAN_EVT0 129 
#define  TXCHAN_EVT1 128 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txch_free ; 

__attribute__((used)) static int pasemi_alloc_tx_chan(enum pasemi_dmachan_type type)
{
	int bit;
	int start, limit;

	switch (type & (TXCHAN_EVT0|TXCHAN_EVT1)) {
	case TXCHAN_EVT0:
		start = 0;
		limit = 10;
		break;
	case TXCHAN_EVT1:
		start = 10;
		limit = MAX_TXCH;
		break;
	default:
		start = 0;
		limit = MAX_TXCH;
		break;
	}
retry:
	bit = find_next_bit(txch_free, MAX_TXCH, start);
	if (bit >= limit)
		return -ENOSPC;
	if (!test_and_clear_bit(bit, txch_free))
		goto retry;

	return bit;
}
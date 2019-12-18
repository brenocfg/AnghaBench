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

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  MAX_RXCH ; 
 int MAX_TXCH ; 
 int find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxch_free ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pasemi_alloc_rx_chan(void)
{
	int bit;
retry:
	bit = find_first_bit(rxch_free, MAX_RXCH);
	if (bit >= MAX_TXCH)
		return -ENOSPC;
	if (!test_and_clear_bit(bit, rxch_free))
		goto retry;

	return bit;
}
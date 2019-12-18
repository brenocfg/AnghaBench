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
struct sdp_sock {int dummy; } ;

/* Variables and functions */
 int MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int SDP_MIN_TX_CREDITS ; 
 scalar_t__ SDP_TX_SIZE ; 
 int /*<<< orphan*/  tx_credits (struct sdp_sock*) ; 
 scalar_t__ tx_ring_posted (struct sdp_sock*) ; 

__attribute__((used)) static inline int tx_slots_free(struct sdp_sock *ssk)
{
	int min_free;

	min_free = MIN(tx_credits(ssk),
			SDP_TX_SIZE - tx_ring_posted(ssk));
	if (min_free < SDP_MIN_TX_CREDITS)
		return 0;

	return min_free - SDP_MIN_TX_CREDITS;
}
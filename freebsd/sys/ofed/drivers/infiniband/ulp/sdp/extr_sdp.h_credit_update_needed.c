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
 int SDP_MIN_TX_CREDITS ; 
 scalar_t__ likely (int) ; 
 int remote_credits (struct sdp_sock*) ; 
 int rx_ring_posted (struct sdp_sock*) ; 
 int sdp_tx_ring_slots_left (struct sdp_sock*) ; 
 scalar_t__ tx_credits (struct sdp_sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int credit_update_needed(struct sdp_sock *ssk)
{
	int c;

	c = remote_credits(ssk);
	if (likely(c > SDP_MIN_TX_CREDITS))
		c += c/2;
	return unlikely(c < rx_ring_posted(ssk)) &&
	    likely(tx_credits(ssk) > 0) &&
	    likely(sdp_tx_ring_slots_left(ssk));
}
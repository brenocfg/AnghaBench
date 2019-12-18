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
 int SDP_TX_SIZE ; 
 int tx_ring_posted (struct sdp_sock*) ; 

__attribute__((used)) static inline int sdp_tx_ring_slots_left(struct sdp_sock *ssk)
{
	return SDP_TX_SIZE - tx_ring_posted(ssk);
}
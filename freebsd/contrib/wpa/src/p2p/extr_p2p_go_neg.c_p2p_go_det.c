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
typedef  int u8 ;

/* Variables and functions */
 int P2P_MAX_GO_INTENT ; 

__attribute__((used)) static int p2p_go_det(u8 own_intent, u8 peer_value)
{
	u8 peer_intent = peer_value >> 1;
	if (own_intent == peer_intent) {
		if (own_intent == P2P_MAX_GO_INTENT)
			return -1; /* both devices want to become GO */

		/* Use tie breaker bit to determine GO */
		return (peer_value & 0x01) ? 0 : 1;
	}

	return own_intent > peer_intent;
}
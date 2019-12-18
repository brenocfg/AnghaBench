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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 

int fst_read_peer_addr(const char *mac, u8 *peer_addr)
{
	if (hwaddr_aton(mac, peer_addr)) {
		fst_printf(MSG_WARNING, "Bad peer_mac %s: invalid addr string",
			   mac);
		return -1;
	}

	if (is_zero_ether_addr(peer_addr) ||
	    is_multicast_ether_addr(peer_addr)) {
		fst_printf(MSG_WARNING, "Bad peer_mac %s: not a unicast addr",
			   mac);
		return -1;
	}

	return 0;
}
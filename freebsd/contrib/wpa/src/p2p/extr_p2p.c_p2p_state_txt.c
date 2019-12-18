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
#define  P2P_CONNECT 140 
#define  P2P_CONNECT_LISTEN 139 
#define  P2P_GO_NEG 138 
#define  P2P_IDLE 137 
#define  P2P_INVITE 136 
#define  P2P_INVITE_LISTEN 135 
#define  P2P_LISTEN_ONLY 134 
#define  P2P_PD_DURING_FIND 133 
#define  P2P_PROVISIONING 132 
#define  P2P_SD_DURING_FIND 131 
#define  P2P_SEARCH 130 
#define  P2P_WAIT_PEER_CONNECT 129 
#define  P2P_WAIT_PEER_IDLE 128 

__attribute__((used)) static const char * p2p_state_txt(int state)
{
	switch (state) {
	case P2P_IDLE:
		return "IDLE";
	case P2P_SEARCH:
		return "SEARCH";
	case P2P_CONNECT:
		return "CONNECT";
	case P2P_CONNECT_LISTEN:
		return "CONNECT_LISTEN";
	case P2P_GO_NEG:
		return "GO_NEG";
	case P2P_LISTEN_ONLY:
		return "LISTEN_ONLY";
	case P2P_WAIT_PEER_CONNECT:
		return "WAIT_PEER_CONNECT";
	case P2P_WAIT_PEER_IDLE:
		return "WAIT_PEER_IDLE";
	case P2P_SD_DURING_FIND:
		return "SD_DURING_FIND";
	case P2P_PROVISIONING:
		return "PROVISIONING";
	case P2P_PD_DURING_FIND:
		return "PD_DURING_FIND";
	case P2P_INVITE:
		return "INVITE";
	case P2P_INVITE_LISTEN:
		return "INVITE_LISTEN";
	default:
		return "?";
	}
}
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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct al_eth_adapter {int /*<<< orphan*/  hal_adapter; } ;

/* Variables and functions */
 int AL_ETH_FSM_DATA_DEFAULT_Q ; 
 int AL_ETH_FSM_DATA_DEFAULT_UDMA ; 
 int AL_ETH_FSM_DATA_HASH_SEL ; 
 int AL_ETH_FSM_DATA_OUTER_2_TUPLE ; 
 int AL_ETH_FSM_DATA_OUTER_4_TUPLE ; 
#define  AL_ETH_FSM_ENTRY_IPV4_NO_UDP_TCP 133 
#define  AL_ETH_FSM_ENTRY_IPV4_TCP 132 
#define  AL_ETH_FSM_ENTRY_IPV4_UDP 131 
#define  AL_ETH_FSM_ENTRY_IPV6_NO_UDP_TCP 130 
#define  AL_ETH_FSM_ENTRY_IPV6_TCP 129 
#define  AL_ETH_FSM_ENTRY_IPV6_UDP 128 
 int AL_ETH_FSM_ENTRY_OUTER (int) ; 
 int AL_ETH_RX_FSM_TABLE_SIZE ; 
 int /*<<< orphan*/  al_eth_fsm_table_set (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
al_eth_fsm_table_init(struct al_eth_adapter *adapter)
{
	uint32_t val;
	int i;

	for (i = 0; i < AL_ETH_RX_FSM_TABLE_SIZE; i++) {
		uint8_t outer_type = AL_ETH_FSM_ENTRY_OUTER(i);
		switch (outer_type) {
		case AL_ETH_FSM_ENTRY_IPV4_TCP:
		case AL_ETH_FSM_ENTRY_IPV4_UDP:
		case AL_ETH_FSM_ENTRY_IPV6_TCP:
		case AL_ETH_FSM_ENTRY_IPV6_UDP:
			val = AL_ETH_FSM_DATA_OUTER_4_TUPLE |
			    AL_ETH_FSM_DATA_HASH_SEL;
			break;
		case AL_ETH_FSM_ENTRY_IPV6_NO_UDP_TCP:
		case AL_ETH_FSM_ENTRY_IPV4_NO_UDP_TCP:
			val = AL_ETH_FSM_DATA_OUTER_2_TUPLE |
			    AL_ETH_FSM_DATA_HASH_SEL;
			break;
		default:
			val = AL_ETH_FSM_DATA_DEFAULT_Q |
			    AL_ETH_FSM_DATA_DEFAULT_UDMA;
		}
		al_eth_fsm_table_set(&adapter->hal_adapter, i, val);
	}
}
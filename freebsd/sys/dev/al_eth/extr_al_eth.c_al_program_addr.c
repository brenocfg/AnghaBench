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
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct al_eth_adapter {int dummy; } ;

/* Variables and functions */
 int AL_ETH_MAC_TABLE_UNICAST_IDX_BASE ; 
 int /*<<< orphan*/  al_eth_mac_table_unicast_add (struct al_eth_adapter*,int,int) ; 

__attribute__((used)) static u_int
al_program_addr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct al_eth_adapter *adapter = arg;

	al_eth_mac_table_unicast_add(adapter,
	    AL_ETH_MAC_TABLE_UNICAST_IDX_BASE + 1 + cnt, 1);

	return (1);
}
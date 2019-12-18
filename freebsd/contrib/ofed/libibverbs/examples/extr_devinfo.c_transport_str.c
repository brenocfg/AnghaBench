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
typedef  enum ibv_transport_type { ____Placeholder_ibv_transport_type } ibv_transport_type ;

/* Variables and functions */
#define  IBV_TRANSPORT_IB 131 
#define  IBV_TRANSPORT_IWARP 130 
#define  IBV_TRANSPORT_USNIC 129 
#define  IBV_TRANSPORT_USNIC_UDP 128 

__attribute__((used)) static const char *transport_str(enum ibv_transport_type transport)
{
	switch (transport) {
	case IBV_TRANSPORT_IB:		return "InfiniBand";
	case IBV_TRANSPORT_IWARP:	return "iWARP";
	case IBV_TRANSPORT_USNIC:	return "usNIC";
	case IBV_TRANSPORT_USNIC_UDP:	return "usNIC UDP";
	default:			return "invalid transport";
	}
}
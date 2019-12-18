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
typedef  int uint32_t ;
struct ena_adapter {int tx_offload_cap; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_TSO ; 
 int CSUM_IP6_UDP ; 
 int CSUM_IP_TCP ; 
 int CSUM_IP_TSO ; 
 int CSUM_IP_UDP ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L3_CSUM_IPV4_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_FULL_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_PART_MASK ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int /*<<< orphan*/  if_clearhwassist (int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_update_hwassist(struct ena_adapter *adapter)
{
	if_t ifp = adapter->ifp;
	uint32_t feat = adapter->tx_offload_cap;
	int cap = if_getcapenable(ifp);
	int flags = 0;

	if_clearhwassist(ifp);

	if ((cap & IFCAP_TXCSUM) != 0) {
		if ((feat &
		    ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L3_CSUM_IPV4_MASK) != 0)
			flags |= CSUM_IP;
		if ((feat &
		    (ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_FULL_MASK |
		    ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_PART_MASK)) != 0)
			flags |= CSUM_IP_UDP | CSUM_IP_TCP;
	}

	if ((cap & IFCAP_TXCSUM_IPV6) != 0)
		flags |= CSUM_IP6_UDP | CSUM_IP6_TCP;

	if ((cap & IFCAP_TSO4) != 0)
		flags |= CSUM_IP_TSO;

	if ((cap & IFCAP_TSO6) != 0)
		flags |= CSUM_IP6_TSO;

	if_sethwassistbits(ifp, flags, 0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tx; int rx_supported; } ;
struct ena_com_dev_get_features_ctx {TYPE_1__ offload; } ;

/* Variables and functions */
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L3_CSUM_IPV4_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV4_CSUM_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV6_CSUM_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV4_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV6_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L3_CSUM_IPV4_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_FULL_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_PART_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_FULL_MASK ; 
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_PART_MASK ; 
 int IFCAP_JUMBO_MTU ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 

__attribute__((used)) static int
ena_get_dev_offloads(struct ena_com_dev_get_features_ctx *feat)
{
	int caps = 0;

	if ((feat->offload.tx &
	    (ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_FULL_MASK |
	    ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_PART_MASK |
	    ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L3_CSUM_IPV4_MASK)) != 0)
		caps |= IFCAP_TXCSUM;

	if ((feat->offload.tx &
	    (ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_FULL_MASK |
	    ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_PART_MASK)) != 0)
		caps |= IFCAP_TXCSUM_IPV6;

	if ((feat->offload.tx &
	    ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV4_MASK) != 0)
		caps |= IFCAP_TSO4;

	if ((feat->offload.tx &
	    ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV6_MASK) != 0)
		caps |= IFCAP_TSO6;

	if ((feat->offload.rx_supported &
	    (ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV4_CSUM_MASK |
	    ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L3_CSUM_IPV4_MASK)) != 0)
		caps |= IFCAP_RXCSUM;

	if ((feat->offload.rx_supported &
	    ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV6_CSUM_MASK) != 0)
		caps |= IFCAP_RXCSUM_IPV6;

	caps |= IFCAP_LRO | IFCAP_JUMBO_MTU;

	return (caps);
}
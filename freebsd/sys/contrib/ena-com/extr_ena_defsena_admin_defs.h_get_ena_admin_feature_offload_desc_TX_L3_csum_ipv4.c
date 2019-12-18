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
struct ena_admin_feature_offload_desc {int tx; } ;

/* Variables and functions */
 int ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L3_CSUM_IPV4_MASK ; 

__attribute__((used)) static inline uint32_t get_ena_admin_feature_offload_desc_TX_L3_csum_ipv4(const struct ena_admin_feature_offload_desc *p)
{
	return p->tx & ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L3_CSUM_IPV4_MASK;
}
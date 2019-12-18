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
struct iavf_sc {int dummy; } ;

/* Variables and functions */
#define  IAVF_FLAG_AQ_ADD_MAC_FILTER 139 
#define  IAVF_FLAG_AQ_ADD_VLAN_FILTER 138 
#define  IAVF_FLAG_AQ_CONFIGURE_PROMISC 137 
#define  IAVF_FLAG_AQ_CONFIGURE_QUEUES 136 
#define  IAVF_FLAG_AQ_CONFIG_RSS_KEY 135 
#define  IAVF_FLAG_AQ_CONFIG_RSS_LUT 134 
#define  IAVF_FLAG_AQ_DEL_MAC_FILTER 133 
#define  IAVF_FLAG_AQ_DEL_VLAN_FILTER 132 
#define  IAVF_FLAG_AQ_DISABLE_QUEUES 131 
#define  IAVF_FLAG_AQ_ENABLE_QUEUES 130 
#define  IAVF_FLAG_AQ_MAP_VECTORS 129 
#define  IAVF_FLAG_AQ_SET_RSS_HENA 128 
 int iavf_add_ether_filters (struct iavf_sc*) ; 
 int iavf_add_vlans (struct iavf_sc*) ; 
 int iavf_config_promisc_mode (struct iavf_sc*) ; 
 int iavf_config_rss_key (struct iavf_sc*) ; 
 int iavf_config_rss_lut (struct iavf_sc*) ; 
 int iavf_configure_queues (struct iavf_sc*) ; 
 int iavf_del_ether_filters (struct iavf_sc*) ; 
 int iavf_del_vlans (struct iavf_sc*) ; 
 int iavf_disable_queues (struct iavf_sc*) ; 
 int iavf_enable_queues (struct iavf_sc*) ; 
 int iavf_map_queues (struct iavf_sc*) ; 
 int iavf_set_rss_hena (struct iavf_sc*) ; 

int
ixl_vc_send_cmd(struct iavf_sc *sc, uint32_t request)
{

	switch (request) {
	case IAVF_FLAG_AQ_MAP_VECTORS:
		return iavf_map_queues(sc);

	case IAVF_FLAG_AQ_ADD_MAC_FILTER:
		return iavf_add_ether_filters(sc);

	case IAVF_FLAG_AQ_ADD_VLAN_FILTER:
		return iavf_add_vlans(sc);

	case IAVF_FLAG_AQ_DEL_MAC_FILTER:
		return iavf_del_ether_filters(sc);

	case IAVF_FLAG_AQ_DEL_VLAN_FILTER:
		return iavf_del_vlans(sc);

	case IAVF_FLAG_AQ_CONFIGURE_QUEUES:
		return iavf_configure_queues(sc);

	case IAVF_FLAG_AQ_DISABLE_QUEUES:
		return iavf_disable_queues(sc);

	case IAVF_FLAG_AQ_ENABLE_QUEUES:
		return iavf_enable_queues(sc);

	case IAVF_FLAG_AQ_CONFIG_RSS_KEY:
		return iavf_config_rss_key(sc);

	case IAVF_FLAG_AQ_SET_RSS_HENA:
		return iavf_set_rss_hena(sc);

	case IAVF_FLAG_AQ_CONFIG_RSS_LUT:
		return iavf_config_rss_lut(sc);

	case IAVF_FLAG_AQ_CONFIGURE_PROMISC:
		return iavf_config_promisc_mode(sc);
	}

	return (0);
}
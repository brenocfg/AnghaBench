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
typedef  int u32 ;
typedef  int u16 ;
struct ecore_dev {int dummy; } ;
typedef  enum ecore_llh_prot_filter_type_t { ____Placeholder_ecore_llh_prot_filter_type_t } ecore_llh_prot_filter_type_t ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*,int) ; 
 int ECORE_INVAL ; 
#define  ECORE_LLH_FILTER_ETHERTYPE 134 
#define  ECORE_LLH_FILTER_TCP_DEST_PORT 133 
#define  ECORE_LLH_FILTER_TCP_SRC_AND_DEST_PORT 132 
#define  ECORE_LLH_FILTER_TCP_SRC_PORT 131 
#define  ECORE_LLH_FILTER_UDP_DEST_PORT 130 
#define  ECORE_LLH_FILTER_UDP_SRC_AND_DEST_PORT 129 
#define  ECORE_LLH_FILTER_UDP_SRC_PORT 128 
 int ECORE_SUCCESS ; 

__attribute__((used)) static enum _ecore_status_t
ecore_llh_protocol_filter_to_hilo(struct ecore_dev *p_dev,
				  enum ecore_llh_prot_filter_type_t type,
				  u16 source_port_or_eth_type, u16 dest_port,
				  u32 *p_high, u32 *p_low)
{
	*p_high = 0;
	*p_low = 0;

	switch (type) {
	case ECORE_LLH_FILTER_ETHERTYPE:
		*p_high = source_port_or_eth_type;
		break;
	case ECORE_LLH_FILTER_TCP_SRC_PORT:
	case ECORE_LLH_FILTER_UDP_SRC_PORT:
		*p_low = source_port_or_eth_type << 16;
		break;
	case ECORE_LLH_FILTER_TCP_DEST_PORT:
	case ECORE_LLH_FILTER_UDP_DEST_PORT:
		*p_low = dest_port;
		break;
	case ECORE_LLH_FILTER_TCP_SRC_AND_DEST_PORT:
	case ECORE_LLH_FILTER_UDP_SRC_AND_DEST_PORT:
		*p_low = (source_port_or_eth_type << 16) | dest_port;
		break;
	default:
		DP_NOTICE(p_dev, true,
			  "Non valid LLH protocol filter type %d\n", type);
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}
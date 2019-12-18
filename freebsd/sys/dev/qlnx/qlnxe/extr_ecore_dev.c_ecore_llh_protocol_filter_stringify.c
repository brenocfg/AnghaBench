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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_dev {int dummy; } ;
typedef  int /*<<< orphan*/  osal_size_t ;
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
 int /*<<< orphan*/  OSAL_SNPRINTF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_llh_protocol_filter_stringify(struct ecore_dev *p_dev,
				    enum ecore_llh_prot_filter_type_t type,
				    u16 source_port_or_eth_type, u16 dest_port,
				    u8 *str, osal_size_t str_len)
{
	switch (type) {
	case ECORE_LLH_FILTER_ETHERTYPE:
		OSAL_SNPRINTF(str, str_len, "Ethertype 0x%04x",
			      source_port_or_eth_type);
		break;
	case ECORE_LLH_FILTER_TCP_SRC_PORT:
		OSAL_SNPRINTF(str, str_len, "TCP src port 0x%04x",
			      source_port_or_eth_type);
		break;
	case ECORE_LLH_FILTER_UDP_SRC_PORT:
		OSAL_SNPRINTF(str, str_len, "UDP src port 0x%04x",
			      source_port_or_eth_type);
		break;
	case ECORE_LLH_FILTER_TCP_DEST_PORT:
		OSAL_SNPRINTF(str, str_len, "TCP dst port 0x%04x", dest_port);
		break;
	case ECORE_LLH_FILTER_UDP_DEST_PORT:
		OSAL_SNPRINTF(str, str_len, "UDP dst port 0x%04x", dest_port);
		break;
	case ECORE_LLH_FILTER_TCP_SRC_AND_DEST_PORT:
		OSAL_SNPRINTF(str, str_len, "TCP src/dst ports 0x%04x/0x%04x",
			      source_port_or_eth_type, dest_port);
		break;
	case ECORE_LLH_FILTER_UDP_SRC_AND_DEST_PORT:
		OSAL_SNPRINTF(str, str_len, "UDP src/dst ports 0x%04x/0x%04x",
			      source_port_or_eth_type, dest_port);
		break;
	default:
		DP_NOTICE(p_dev, true,
			  "Non valid LLH protocol filter type %d\n", type);
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}
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
typedef  int bpf_u_int32 ;

/* Variables and functions */
#define  DL_ATTACH_REQ 154 
#define  DL_BIND_ACK 153 
#define  DL_BIND_REQ 152 
#define  DL_CONNECT_CON 151 
#define  DL_CONNECT_IND 150 
#define  DL_CONNECT_REQ 149 
#define  DL_CONNECT_RES 148 
#define  DL_DETACH_REQ 147 
#define  DL_DISCONNECT_IND 146 
#define  DL_DISCONNECT_REQ 145 
#define  DL_ERROR_ACK 144 
#define  DL_INFO_ACK 143 
#define  DL_INFO_REQ 142 
#define  DL_OK_ACK 141 
#define  DL_RESET_CON 140 
#define  DL_RESET_IND 139 
#define  DL_RESET_REQ 138 
#define  DL_RESET_RES 137 
#define  DL_SUBS_BIND_ACK 136 
#define  DL_SUBS_BIND_REQ 135 
#define  DL_TOKEN_ACK 134 
#define  DL_TOKEN_REQ 133 
#define  DL_UDERROR_IND 132 
#define  DL_UDQOS_REQ 131 
#define  DL_UNBIND_REQ 130 
#define  DL_UNITDATA_IND 129 
#define  DL_UNITDATA_REQ 128 
 int /*<<< orphan*/  pcap_snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static char *
dlprim(char *primbuf, size_t primbufsize, bpf_u_int32 prim)
{
	switch (prim) {

	case DL_INFO_REQ:
		return ("DL_INFO_REQ");

	case DL_INFO_ACK:
		return ("DL_INFO_ACK");

	case DL_ATTACH_REQ:
		return ("DL_ATTACH_REQ");

	case DL_DETACH_REQ:
		return ("DL_DETACH_REQ");

	case DL_BIND_REQ:
		return ("DL_BIND_REQ");

	case DL_BIND_ACK:
		return ("DL_BIND_ACK");

	case DL_UNBIND_REQ:
		return ("DL_UNBIND_REQ");

	case DL_OK_ACK:
		return ("DL_OK_ACK");

	case DL_ERROR_ACK:
		return ("DL_ERROR_ACK");

	case DL_SUBS_BIND_REQ:
		return ("DL_SUBS_BIND_REQ");

	case DL_SUBS_BIND_ACK:
		return ("DL_SUBS_BIND_ACK");

	case DL_UNITDATA_REQ:
		return ("DL_UNITDATA_REQ");

	case DL_UNITDATA_IND:
		return ("DL_UNITDATA_IND");

	case DL_UDERROR_IND:
		return ("DL_UDERROR_IND");

	case DL_UDQOS_REQ:
		return ("DL_UDQOS_REQ");

	case DL_CONNECT_REQ:
		return ("DL_CONNECT_REQ");

	case DL_CONNECT_IND:
		return ("DL_CONNECT_IND");

	case DL_CONNECT_RES:
		return ("DL_CONNECT_RES");

	case DL_CONNECT_CON:
		return ("DL_CONNECT_CON");

	case DL_TOKEN_REQ:
		return ("DL_TOKEN_REQ");

	case DL_TOKEN_ACK:
		return ("DL_TOKEN_ACK");

	case DL_DISCONNECT_REQ:
		return ("DL_DISCONNECT_REQ");

	case DL_DISCONNECT_IND:
		return ("DL_DISCONNECT_IND");

	case DL_RESET_REQ:
		return ("DL_RESET_REQ");

	case DL_RESET_IND:
		return ("DL_RESET_IND");

	case DL_RESET_RES:
		return ("DL_RESET_RES");

	case DL_RESET_CON:
		return ("DL_RESET_CON");

	default:
		pcap_snprintf(primbuf, primbufsize, "unknown primitive 0x%x",
		    prim);
		return (primbuf);
	}
}
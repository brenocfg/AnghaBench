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
typedef  enum fman_kg_gen_extract_src { ____Placeholder_fman_kg_gen_extract_src } fman_kg_gen_extract_src ;

/* Variables and functions */
#define  E_FMAN_KG_GEN_EXTRACT_DCCP 157 
#define  E_FMAN_KG_GEN_EXTRACT_ETH 156 
#define  E_FMAN_KG_GEN_EXTRACT_ETYPE 155 
#define  E_FMAN_KG_GEN_EXTRACT_FROM_DFLT 154 
#define  E_FMAN_KG_GEN_EXTRACT_FROM_END_OF_PARSE 153 
#define  E_FMAN_KG_GEN_EXTRACT_FROM_FQID 152 
#define  E_FMAN_KG_GEN_EXTRACT_FROM_FRAME_START 151 
#define  E_FMAN_KG_GEN_EXTRACT_FROM_PARSE_RESULT 150 
#define  E_FMAN_KG_GEN_EXTRACT_GRE 149 
#define  E_FMAN_KG_GEN_EXTRACT_IPSEC_AH 148 
#define  E_FMAN_KG_GEN_EXTRACT_IPSEC_ESP 147 
#define  E_FMAN_KG_GEN_EXTRACT_IP_PID 146 
#define  E_FMAN_KG_GEN_EXTRACT_IPv4_1 145 
#define  E_FMAN_KG_GEN_EXTRACT_IPv4_2 144 
#define  E_FMAN_KG_GEN_EXTRACT_IPv6_1 143 
#define  E_FMAN_KG_GEN_EXTRACT_IPv6_2 142 
#define  E_FMAN_KG_GEN_EXTRACT_MINENCAP 141 
#define  E_FMAN_KG_GEN_EXTRACT_MPLS_1 140 
#define  E_FMAN_KG_GEN_EXTRACT_MPLS_2 139 
#define  E_FMAN_KG_GEN_EXTRACT_MPLS_3 138 
#define  E_FMAN_KG_GEN_EXTRACT_MPLS_N 137 
#define  E_FMAN_KG_GEN_EXTRACT_PPPoE 136 
#define  E_FMAN_KG_GEN_EXTRACT_SCTP 135 
#define  E_FMAN_KG_GEN_EXTRACT_SHIM_1 134 
#define  E_FMAN_KG_GEN_EXTRACT_SHIM_2 133 
#define  E_FMAN_KG_GEN_EXTRACT_SNAP 132 
#define  E_FMAN_KG_GEN_EXTRACT_TCP 131 
#define  E_FMAN_KG_GEN_EXTRACT_UDP 130 
#define  E_FMAN_KG_GEN_EXTRACT_VLAN_TCI_1 129 
#define  E_FMAN_KG_GEN_EXTRACT_VLAN_TCI_N 128 
 int FM_KG_SCH_GEN_HT_INVALID ; 

__attribute__((used)) static uint8_t get_gen_ht_code(enum fman_kg_gen_extract_src src,
				bool no_validation,
				uint8_t *offset)
{
	int	code;

	switch (src) {
	case E_FMAN_KG_GEN_EXTRACT_ETH:
		code = no_validation ? 0x73 : 0x3;
		break;

	case E_FMAN_KG_GEN_EXTRACT_ETYPE:
		code = no_validation ? 0x77 : 0x7;
		break;
 
	case E_FMAN_KG_GEN_EXTRACT_SNAP:
		code = no_validation ? 0x74 : 0x4;
		break;

	case E_FMAN_KG_GEN_EXTRACT_VLAN_TCI_1:
		code = no_validation ? 0x75 : 0x5;
		break;

	case E_FMAN_KG_GEN_EXTRACT_VLAN_TCI_N:
		code = no_validation ? 0x76 : 0x6;
		break;

	case E_FMAN_KG_GEN_EXTRACT_PPPoE:
		code = no_validation ? 0x78 : 0x8;
		break;

	case E_FMAN_KG_GEN_EXTRACT_MPLS_1:
		code = no_validation ? 0x79 : 0x9;
		break;

	case E_FMAN_KG_GEN_EXTRACT_MPLS_2:
		code = no_validation ? FM_KG_SCH_GEN_HT_INVALID : 0x19;
		break;

	case E_FMAN_KG_GEN_EXTRACT_MPLS_3:
		code = no_validation ? FM_KG_SCH_GEN_HT_INVALID : 0x29;
		break;

	case E_FMAN_KG_GEN_EXTRACT_MPLS_N:
		code = no_validation ? 0x7a : 0xa;
		break;

	case E_FMAN_KG_GEN_EXTRACT_IPv4_1:
		code = no_validation ? 0x7b : 0xb;
		break;

	case E_FMAN_KG_GEN_EXTRACT_IPv6_1:
		code = no_validation ? 0x7b : 0x1b;
		break;

	case E_FMAN_KG_GEN_EXTRACT_IPv4_2:
		code = no_validation ? 0x7c : 0xc;
		break;

	case E_FMAN_KG_GEN_EXTRACT_IPv6_2:
		code = no_validation ? 0x7c : 0x1c;
		break;

	case E_FMAN_KG_GEN_EXTRACT_MINENCAP:
		code = no_validation ? 0x7c : 0x2c;
		break;

	case E_FMAN_KG_GEN_EXTRACT_IP_PID:
		code = no_validation ? 0x72 : 0x2;
		break;

	case E_FMAN_KG_GEN_EXTRACT_GRE:
		code = no_validation ? 0x7d : 0xd;
		break;

	case E_FMAN_KG_GEN_EXTRACT_TCP:
		code = no_validation ? 0x7e : 0xe;
		break;

	case E_FMAN_KG_GEN_EXTRACT_UDP:
		code = no_validation ? 0x7e : 0x1e;
		break;

	case E_FMAN_KG_GEN_EXTRACT_SCTP:
		code = no_validation ? 0x7e : 0x3e;
		break;

	case E_FMAN_KG_GEN_EXTRACT_DCCP:
		code = no_validation ? 0x7e : 0x4e;
		break;

	case E_FMAN_KG_GEN_EXTRACT_IPSEC_AH:
		code = no_validation ? 0x7e : 0x2e;
		break;

	case E_FMAN_KG_GEN_EXTRACT_IPSEC_ESP:
		code = no_validation ? 0x7e : 0x6e;
		break;

	case E_FMAN_KG_GEN_EXTRACT_SHIM_1:
		code = 0x70;
		break;

	case E_FMAN_KG_GEN_EXTRACT_SHIM_2:
		code = 0x71;
		break;

	case E_FMAN_KG_GEN_EXTRACT_FROM_DFLT:
		code = 0x10;
		break;

	case E_FMAN_KG_GEN_EXTRACT_FROM_FRAME_START:
		code = 0x40;
		break;

	case E_FMAN_KG_GEN_EXTRACT_FROM_PARSE_RESULT:
		code = 0x20;
		break;

	case E_FMAN_KG_GEN_EXTRACT_FROM_END_OF_PARSE:
		code = 0x7f;
		break;

	case E_FMAN_KG_GEN_EXTRACT_FROM_FQID:
		code = 0x20;
		*offset += 0x20;
		break;

	default:
		code = FM_KG_SCH_GEN_HT_INVALID;
	}

	return (uint8_t)code;
}
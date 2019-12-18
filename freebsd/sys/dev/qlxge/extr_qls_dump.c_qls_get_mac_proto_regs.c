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
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q81_CTL_MAC_PROTO_ADDR_DATA ; 
 int /*<<< orphan*/  Q81_CTL_MAC_PROTO_ADDR_INDEX ; 
 int Q81_NUM_TYPES ; 
 int Q81_RS_AND_ADR ; 
 int Q81_RS_ONLY ; 
 int READ_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
qls_get_mac_proto_regs(qla_host_t *ha, uint32_t* buf)
{

#define Q81_RS_AND_ADR 0x06000000
#define Q81_RS_ONLY    0x04000000
#define Q81_NUM_TYPES  10

	uint32_t result_index, result_data;
	uint32_t type;
	uint32_t index;
	uint32_t offset;
	uint32_t val;
	uint32_t initial_val;
	uint32_t max_index;
	uint32_t max_offset;

	for (type = 0; type < Q81_NUM_TYPES; type ++) {
		switch (type) {

		case 0: // CAM
			initial_val = Q81_RS_AND_ADR;
			max_index = 512;
			max_offset = 3;
			break;

		case 1: // Multicast MAC Address
			initial_val = Q81_RS_ONLY;
			max_index = 32;
			max_offset = 2;
			break;

		case 2: // VLAN filter mask
		case 3: // MC filter mask
			initial_val = Q81_RS_ONLY;
			max_index = 4096;
			max_offset = 1;
			break;

		case 4: // FC MAC addresses
			initial_val = Q81_RS_ONLY;
			max_index = 4;
			max_offset = 2;
			break;

		case 5: // Mgmt MAC addresses
			initial_val = Q81_RS_ONLY;
			max_index = 8;
			max_offset = 2;
			break;

		case 6: // Mgmt VLAN addresses
			initial_val = Q81_RS_ONLY;
			max_index = 16;
			max_offset = 1;
			break;

		case 7: // Mgmt IPv4 address
			initial_val = Q81_RS_ONLY;
			max_index = 4;
			max_offset = 1;
			break;

		case 8: // Mgmt IPv6 address
			initial_val = Q81_RS_ONLY;
			max_index = 4;
			max_offset = 4;
			break;

		case 9: // Mgmt TCP/UDP Dest port
			initial_val = Q81_RS_ONLY;
			max_index = 4;
			max_offset = 1;
			break;

		default:
			printf("Bad type!!! 0x%08x\n", type);
			max_index = 0;
			max_offset = 0;
			break;
		}

		for (index = 0; index < max_index; index ++) {

			for (offset = 0; offset < max_offset; offset ++) {

				val = initial_val | (type << 16) |
					(index << 4) | (offset);

				WRITE_REG32(ha, Q81_CTL_MAC_PROTO_ADDR_INDEX,\
					val);

				result_index = 0;

				while ((result_index & 0x40000000) == 0)
					result_index =
						READ_REG32(ha, \
						Q81_CTL_MAC_PROTO_ADDR_INDEX);

				result_data = READ_REG32(ha,\
						Q81_CTL_MAC_PROTO_ADDR_DATA);

				*buf = result_index;
				buf ++;

				*buf = result_data;
				buf ++;
			}
		}
	}
}
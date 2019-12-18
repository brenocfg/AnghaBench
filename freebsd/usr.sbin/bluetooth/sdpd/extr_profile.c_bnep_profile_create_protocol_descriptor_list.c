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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ptype ;
typedef  int /*<<< orphan*/  psm ;
typedef  int int32_t ;

/* Variables and functions */
 int SDP_DATA_SEQ8 ; 
 int SDP_DATA_UINT16 ; 
 int SDP_DATA_UUID16 ; 
 int /*<<< orphan*/  SDP_PUT16 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT8 (int,int /*<<< orphan*/  const*) ; 
 int SDP_UUID_PROTOCOL_BNEP ; 
 int SDP_UUID_PROTOCOL_L2CAP ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

int32_t
bnep_profile_create_protocol_descriptor_list(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	/* supported protocol types */
	uint16_t	 ptype[] = {
		0x0800,	/* IPv4 */
		0x0806,	/* ARP */
#ifdef INET6
		0x86dd,	/* IPv6 */
#endif
	};

	uint16_t	 i, psm, version = 0x0100,
			 nptypes = sizeof(ptype)/sizeof(ptype[0]),
			 nptypes_size = nptypes * 3;

	if (datalen != 2 || 18 + nptypes_size > 255 ||
	    buf + 20 + nptypes_size > eob)
		return (-1);

	memcpy(&psm, data, sizeof(psm));

	SDP_PUT8(SDP_DATA_SEQ8, buf);
	SDP_PUT8(18 + nptypes_size, buf);

	SDP_PUT8(SDP_DATA_SEQ8, buf);
	SDP_PUT8(6, buf);
	SDP_PUT8(SDP_DATA_UUID16, buf);
	SDP_PUT16(SDP_UUID_PROTOCOL_L2CAP, buf);
	SDP_PUT8(SDP_DATA_UINT16, buf);
	SDP_PUT16(psm, buf);
	
	SDP_PUT8(SDP_DATA_SEQ8, buf);
	SDP_PUT8(8 + nptypes_size, buf);
	SDP_PUT8(SDP_DATA_UUID16, buf);
	SDP_PUT16(SDP_UUID_PROTOCOL_BNEP, buf);
	SDP_PUT8(SDP_DATA_UINT16, buf);
	SDP_PUT16(version, buf);
	SDP_PUT8(SDP_DATA_SEQ8, buf);
	SDP_PUT8(nptypes_size, buf);
	for (i = 0; i < nptypes; i ++) {
		SDP_PUT8(SDP_DATA_UINT16, buf);
		SDP_PUT16(ptype[i], buf);
	}

	return (20 + nptypes_size);
}
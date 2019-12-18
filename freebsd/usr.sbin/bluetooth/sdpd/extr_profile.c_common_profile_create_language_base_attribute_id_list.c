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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int SDP_ATTR_PRIMARY_LANGUAGE_BASE_ID ; 
 int SDP_DATA_SEQ8 ; 
 int SDP_DATA_UINT16 ; 
 int /*<<< orphan*/  SDP_PUT16 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT8 (int,int /*<<< orphan*/  const*) ; 

int32_t
common_profile_create_language_base_attribute_id_list(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	if (buf + 11 > eob)
		return (-1);

	SDP_PUT8(SDP_DATA_SEQ8, buf);
	SDP_PUT8(9, buf);

	/*
	 * Language code per ISO 639:1988. Use "en".
	 */

	SDP_PUT8(SDP_DATA_UINT16, buf);
	SDP_PUT16(((0x65 << 8) | 0x6e), buf);

	/* 
	 * Encoding. Recommended is UTF-8. ISO639 UTF-8 MIBenum is 106 
	 * (http://www.iana.org/assignments/character-sets)
	 */

	SDP_PUT8(SDP_DATA_UINT16, buf);
	SDP_PUT16(106, buf);

	/* 
	 * Offset (Primary Language Base is 0x100)
	 */

	SDP_PUT8(SDP_DATA_UINT16, buf);
	SDP_PUT16(SDP_ATTR_PRIMARY_LANGUAGE_BASE_ID, buf);

	return (11);
}
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
 int SDP_DATA_SEQ8 ; 
 int SDP_DATA_UINT16 ; 
 int /*<<< orphan*/  SDP_PUT16 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT8 (int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int32_t
sd_profile_create_version_number_list(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	if (buf + 5 > eob)
		return (-1);

	SDP_PUT8(SDP_DATA_SEQ8, buf);
	SDP_PUT8(3, buf);

	/* 
	 * The VersionNumberList is a data element sequence in which each 
	 * element of the sequence is a version number supported by the SDP
	 * server. A version number is a 16-bit unsigned integer consisting
	 * of two fields. The higher-order 8 bits contain the major version
	 * number field and the low-order 8 bits contain the minor version
	 * number field. The initial version of SDP has a major version of
	 * 1 and a minor version of 0
	 */

	SDP_PUT8(SDP_DATA_UINT16, buf);
	SDP_PUT16(0x0100, buf);

	return (5);
}
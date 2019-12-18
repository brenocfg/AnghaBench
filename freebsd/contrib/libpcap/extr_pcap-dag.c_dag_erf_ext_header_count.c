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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static unsigned int
dag_erf_ext_header_count(uint8_t * erf, size_t len)
{
	uint32_t hdr_num = 0;
	uint8_t  hdr_type;

	/* basic sanity checks */
	if ( erf == NULL )
		return 0;
	if ( len < 16 )
		return 0;

	/* check if we have any extension headers */
	if ( (erf[8] & 0x80) == 0x00 )
		return 0;

	/* loop over the extension headers */
	do {

		/* sanity check we have enough bytes */
		if ( len < (24 + (hdr_num * 8)) )
			return hdr_num;

		/* get the header type */
		hdr_type = erf[(16 + (hdr_num * 8))];
		hdr_num++;

	} while ( hdr_type & 0x80 );

	return hdr_num;
}
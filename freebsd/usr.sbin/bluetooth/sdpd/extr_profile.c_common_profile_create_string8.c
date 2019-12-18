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
typedef  int int32_t ;

/* Variables and functions */
 int SDP_DATA_STR8 ; 
 int /*<<< orphan*/  SDP_PUT8 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

int32_t
common_profile_create_string8(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	if (datalen == 0 || datalen > 0xff || buf + 2 + datalen > eob)
		return (-1);

	SDP_PUT8(SDP_DATA_STR8, buf);
	SDP_PUT8(datalen, buf);
	memcpy(buf, data, datalen);

	return (2 + datalen);
}
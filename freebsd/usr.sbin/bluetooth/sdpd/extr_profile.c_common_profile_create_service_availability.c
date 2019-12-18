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
 int /*<<< orphan*/  const SDP_DATA_UINT8 ; 
 int /*<<< orphan*/  SDP_PUT8 (int /*<<< orphan*/  const,int /*<<< orphan*/  const*) ; 

int32_t
common_profile_create_service_availability(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	if (datalen != 1 || buf + 2 > eob)
		return (-1);

	SDP_PUT8(SDP_DATA_UINT8, buf);
	SDP_PUT8(data[0], buf);

	return (2);
}
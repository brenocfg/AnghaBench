#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* provider_p ;
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_DATA_UINT32 ; 
 int /*<<< orphan*/  SDP_PUT32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int32_t
common_profile_create_service_record_handle(
	uint8_t *buf, uint8_t const * const eob,
	uint8_t const *data, uint32_t datalen)
{
	if (buf + 5 > eob)
		return (-1);

	SDP_PUT8(SDP_DATA_UINT32, buf);
	SDP_PUT32(((provider_p) data)->handle, buf);

	return (5);
}
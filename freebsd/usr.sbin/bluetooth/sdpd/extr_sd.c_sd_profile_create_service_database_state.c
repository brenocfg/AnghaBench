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
 int /*<<< orphan*/  SDP_DATA_UINT32 ; 
 int /*<<< orphan*/  SDP_PUT32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  provider_get_change_state () ; 

__attribute__((used)) static int32_t
sd_profile_create_service_database_state(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	uint32_t	change_state = provider_get_change_state();

	if (buf + 5 > eob)
		return (-1);

	SDP_PUT8(SDP_DATA_UINT32, buf);
	SDP_PUT32(change_state, buf);

	return (5);
}
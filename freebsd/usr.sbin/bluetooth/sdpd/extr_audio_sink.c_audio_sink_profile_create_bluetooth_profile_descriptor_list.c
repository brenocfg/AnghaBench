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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  profile_descriptor_list ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  SDP_SERVICE_CLASS_ADVANCED_AUDIO_DISTRIBUTION 128 
 int /*<<< orphan*/  common_profile_create_bluetooth_profile_descriptor_list (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int32_t
audio_sink_profile_create_bluetooth_profile_descriptor_list(
    uint8_t *buf, uint8_t const *const eob,
    uint8_t const *data, uint32_t datalen)
{
	static const uint16_t profile_descriptor_list[] = {
		SDP_SERVICE_CLASS_ADVANCED_AUDIO_DISTRIBUTION,
		0x0100
	};

	return (common_profile_create_bluetooth_profile_descriptor_list(
	    buf, eob,
	    (uint8_t const *)profile_descriptor_list,
	    sizeof(profile_descriptor_list)));
}
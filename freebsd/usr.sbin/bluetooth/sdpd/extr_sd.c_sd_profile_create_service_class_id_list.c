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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  service_classes ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  SDP_SERVICE_CLASS_SERVICE_DISCOVERY_SERVER 128 
 int /*<<< orphan*/  common_profile_create_service_class_id_list (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int32_t
sd_profile_create_service_class_id_list(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	static uint16_t	service_classes[] = {
		SDP_SERVICE_CLASS_SERVICE_DISCOVERY_SERVER
	};

	return (common_profile_create_service_class_id_list(
			buf, eob,
			(uint8_t const *) service_classes,
			sizeof(service_classes)));
}
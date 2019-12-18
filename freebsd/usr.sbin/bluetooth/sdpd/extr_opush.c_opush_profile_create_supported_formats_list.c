#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* sdp_opush_profile_p ;
typedef  TYPE_2__* provider_p ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  supported_formats_size; scalar_t__ supported_formats; } ;

/* Variables and functions */
 int /*<<< orphan*/  obex_profile_create_supported_formats_list (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
opush_profile_create_supported_formats_list(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	provider_p		provider = (provider_p) data;
	sdp_opush_profile_p	opush = (sdp_opush_profile_p) provider->data;

	return (obex_profile_create_supported_formats_list(
			buf, eob,
			(uint8_t const *) opush->supported_formats,
			opush->supported_formats_size));
}
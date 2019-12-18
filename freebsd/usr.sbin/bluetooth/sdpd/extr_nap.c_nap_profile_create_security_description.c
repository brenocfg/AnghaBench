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
typedef  TYPE_1__* sdp_nap_profile_p ;
typedef  TYPE_2__* provider_p ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  security_description; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnep_profile_create_security_description (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int32_t
nap_profile_create_security_description(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	provider_p		provider = (provider_p) data; 
	sdp_nap_profile_p	nap = (sdp_nap_profile_p) provider->data; 

	return (bnep_profile_create_security_description(buf, eob,
			(uint8_t const *) &nap->security_description,
			sizeof(nap->security_description)));
}
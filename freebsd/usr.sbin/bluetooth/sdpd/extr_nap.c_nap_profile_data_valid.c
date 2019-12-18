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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* sdp_nap_profile_p ;
typedef  int int32_t ;
struct TYPE_2__ {scalar_t__ psm; } ;

/* Variables and functions */

__attribute__((used)) static int32_t
nap_profile_data_valid(uint8_t const *data, uint32_t datalen)
{
	sdp_nap_profile_p	nap = (sdp_nap_profile_p) data;

	return ((nap->psm == 0)? 0 : 1);
}
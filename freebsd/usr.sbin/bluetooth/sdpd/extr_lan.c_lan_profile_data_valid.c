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
typedef  TYPE_1__* sdp_lan_profile_p ;
typedef  int int32_t ;
struct TYPE_2__ {int server_channel; int ip_subnet_radius; } ;

/* Variables and functions */

__attribute__((used)) static int32_t
lan_profile_data_valid(uint8_t const *data, uint32_t datalen)
{
	sdp_lan_profile_p	lan = (sdp_lan_profile_p) data;

	if (lan->server_channel < 1 ||
	    lan->server_channel > 30 ||
	    lan->ip_subnet_radius > 32)
		return (0);

	return (1);
}
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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct in_addr {int dummy; } ;
typedef  TYPE_1__* sdp_lan_profile_p ;
typedef  TYPE_2__* provider_p ;
typedef  int /*<<< orphan*/  net ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int ip_subnet_radius; int /*<<< orphan*/  ip_subnet; } ;

/* Variables and functions */
 scalar_t__ SDP_DATA_STR8 ; 
 int /*<<< orphan*/  SDP_PUT8 (scalar_t__,int /*<<< orphan*/  const*) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,char*,scalar_t__) ; 
 scalar_t__ snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int32_t
lan_profile_create_ip_subnet(
		uint8_t *buf, uint8_t const * const eob,
		uint8_t const *data, uint32_t datalen)
{
	provider_p		provider = (provider_p) data;
	sdp_lan_profile_p	lan = (sdp_lan_profile_p) provider->data;
	char			net[32];
	int32_t			len;

	len = snprintf(net, sizeof(net), "%s/%d",
			inet_ntoa(* (struct in_addr *) &lan->ip_subnet),
			lan->ip_subnet_radius);

	if (len < 0 || buf + 2 + len > eob)
		return (-1);

	SDP_PUT8(SDP_DATA_STR8, buf);
	SDP_PUT8(len, buf);
	memcpy(buf, net, len);

	return (2 + len);
}
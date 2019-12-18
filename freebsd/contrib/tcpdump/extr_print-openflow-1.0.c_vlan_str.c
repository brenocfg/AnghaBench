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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int const OFP_VLAN_NONE ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int const) ; 

__attribute__((used)) static const char *
vlan_str(const uint16_t vid)
{
	static char buf[sizeof("65535 (bogus)")];
	const char *fmt;

	if (vid == OFP_VLAN_NONE)
		return "NONE";
	fmt = (vid > 0 && vid < 0x0fff) ? "%u" : "%u (bogus)";
	snprintf(buf, sizeof(buf), fmt, vid);
	return buf;
}
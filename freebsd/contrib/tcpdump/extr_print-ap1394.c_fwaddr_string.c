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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  FIREWIRE_EUI64_LEN ; 
 int /*<<< orphan*/  LINKADDR_IEEE1394 ; 
 char const* linkaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
fwaddr_string(netdissect_options *ndo, const u_char *addr)
{
	return (linkaddr_string(ndo, addr, LINKADDR_IEEE1394, FIREWIRE_EUI64_LEN));
}
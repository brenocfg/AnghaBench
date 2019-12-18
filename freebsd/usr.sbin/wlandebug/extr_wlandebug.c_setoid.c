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

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static void
setoid(char oid[], size_t oidlen, const char *wlan)
{
#ifdef __linux__
	if (wlan)
		snprintf(oid, oidlen, "net.%s.debug", wlan);
#elif __FreeBSD__
	if (wlan)
		snprintf(oid, oidlen, "net.wlan.%s.debug", wlan+4);
	else
		snprintf(oid, oidlen, "net.wlan.debug");
#elif __NetBSD__
	if (wlan)
		snprintf(oid, oidlen, "net.link.ieee80211.%s.debug", wlan);
	else
		snprintf(oid, oidlen, "net.link.ieee80211.debug");
#else
#error "No support for this system"
#endif
}
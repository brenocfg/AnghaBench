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
struct TYPE_2__ {int /*<<< orphan*/  v6; int /*<<< orphan*/  v4; } ;
struct hostapd_ip_addr {int /*<<< orphan*/  af; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ inet_aton (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

int hostapd_parse_ip_addr(const char *txt, struct hostapd_ip_addr *addr)
{
#ifndef CONFIG_NATIVE_WINDOWS
	if (inet_aton(txt, &addr->u.v4)) {
		addr->af = AF_INET;
		return 0;
	}

#ifdef CONFIG_IPV6
	if (inet_pton(AF_INET6, txt, &addr->u.v6) > 0) {
		addr->af = AF_INET6;
		return 0;
	}
#endif /* CONFIG_IPV6 */
#endif /* CONFIG_NATIVE_WINDOWS */

	return -1;
}
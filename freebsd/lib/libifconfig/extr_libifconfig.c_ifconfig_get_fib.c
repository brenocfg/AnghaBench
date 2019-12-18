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
struct ifreq {int ifr_fib; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  SIOCGIFFIB ; 
 int ifconfig_ioctlwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
ifconfig_get_fib(ifconfig_handle_t *h, const char *name, int *fib)
{
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(ifr));
	(void)strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));

	if (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCGIFFIB, &ifr) == -1) {
		return (-1);
	}

	*fib = ifr.ifr_fib;
	return (0);
}
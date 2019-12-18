#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct in6_ndireq {TYPE_1__ ndi; int /*<<< orphan*/  ifname; } ;
struct TYPE_8__ {scalar_t__ errtype; } ;
struct TYPE_9__ {TYPE_2__ error; } ;
typedef  TYPE_3__ ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ND6_IFF_DEFAULTIF ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  SIOCGIFINFO_IN6 ; 
 int ifconfig_ioctlwrap (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_ndireq*) ; 
 scalar_t__ isnd6defif (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  memset (struct in6_ndireq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
ifconfig_get_nd6(ifconfig_handle_t *h, const char *name,
    struct in6_ndireq *nd)
{
	memset(nd, 0, sizeof(*nd));
	strlcpy(nd->ifname, name, sizeof(nd->ifname));
	if (ifconfig_ioctlwrap(h, AF_INET6, SIOCGIFINFO_IN6, nd) == -1) {
		return (-1);
	}
	if (isnd6defif(h, name)) {
		nd->ndi.flags |= ND6_IFF_DEFAULTIF;
	} else if (h->error.errtype != OK) {
		return (-1);
	}

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ifgroupreq {int ifgr_len; struct ifg_req* ifgr_groups; int /*<<< orphan*/  ifgr_name; } ;
struct ifg_req {int dummy; } ;
struct TYPE_5__ {scalar_t__ errcode; } ;
struct TYPE_6__ {TYPE_1__ error; } ;
typedef  TYPE_2__ ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOTTY ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCGIFGROUP ; 
 int /*<<< orphan*/  bzero (struct ifg_req*,int) ; 
 int ifconfig_ioctlwrap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifgroupreq*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct ifgroupreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
ifconfig_get_groups(ifconfig_handle_t *h, const char *name,
    struct ifgroupreq *ifgr)
{
	int len;

	memset(ifgr, 0, sizeof(*ifgr));
	strlcpy(ifgr->ifgr_name, name, IFNAMSIZ);

	if (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCGIFGROUP, ifgr) == -1) {
		if ((h->error.errcode == EINVAL) ||
		    (h->error.errcode == ENOTTY)) {
			return (0);
		} else {
			return (-1);
		}
	}

	len = ifgr->ifgr_len;
	ifgr->ifgr_groups = (struct ifg_req *)malloc(len);
	if (ifgr->ifgr_groups == NULL) {
		return (1);
	}
	bzero(ifgr->ifgr_groups, len);
	if (ifconfig_ioctlwrap(h, AF_LOCAL, SIOCGIFGROUP, ifgr) == -1) {
		return (-1);
	}

	return (0);
}
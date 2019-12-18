#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ errcode; int /*<<< orphan*/  errtype; } ;
struct TYPE_5__ {TYPE_1__ error; } ;
typedef  TYPE_2__ ifconfig_handle_t ;

/* Variables and functions */
 int CTL_NET ; 
 scalar_t__ ENOENT ; 
 int IFDATA_DRIVERNAME ; 
 int IFMIB_IFDATA ; 
 int NETLINK_GENERIC ; 
 int /*<<< orphan*/  OTHER ; 
 int PF_LINK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 unsigned int if_nametoindex (char const*) ; 
 char* malloc (size_t) ; 
 scalar_t__ sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ifconfig_get_orig_name(ifconfig_handle_t *h, const char *ifname,
    char **orig_name)
{
	size_t len;
	unsigned int ifindex;
	int name[6];

	ifindex = if_nametoindex(ifname);
	if (ifindex == 0) {
		goto fail;
	}

	name[0] = CTL_NET;
	name[1] = PF_LINK;
	name[2] = NETLINK_GENERIC;
	name[3] = IFMIB_IFDATA;
	name[4] = ifindex;
	name[5] = IFDATA_DRIVERNAME;

	len = 0;
	if (sysctl(name, 6, NULL, &len, 0, 0) < 0) {
		goto fail;
	}

	*orig_name = malloc(len);
	if (*orig_name == NULL) {
		goto fail;
	}

	if (sysctl(name, 6, *orig_name, &len, 0, 0) < 0) {
		free(*orig_name);
		*orig_name = NULL;
		goto fail;
	}

	return (0);

fail:
	h->error.errtype = OTHER;
	h->error.errcode = (errno != 0) ? errno : ENOENT;
	return (-1);
}
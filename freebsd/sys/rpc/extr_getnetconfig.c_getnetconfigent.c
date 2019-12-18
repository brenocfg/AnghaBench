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
struct netconfig {scalar_t__ nc_netid; } ;

/* Variables and functions */
 struct netconfig* netconfigs ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

struct netconfig *
getnetconfigent(const char *netid)
{
	struct netconfig *nconf;

	for (nconf = netconfigs; nconf->nc_netid; nconf++) {
		if (!strcmp(netid, nconf->nc_netid))
			return (nconf);
	}

	return (NULL);
}
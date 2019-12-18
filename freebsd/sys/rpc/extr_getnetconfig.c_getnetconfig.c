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
struct netconfig {int /*<<< orphan*/ * nc_netid; } ;

/* Variables and functions */

struct netconfig *
getnetconfig(void *handle)
{
	struct netconfig **nconfp = (struct netconfig **) handle;
	struct netconfig *nconf;

	nconf = *nconfp;
	if (nconf->nc_netid == NULL)
		return (NULL);

	(*nconfp)++;

	return (nconf);
}
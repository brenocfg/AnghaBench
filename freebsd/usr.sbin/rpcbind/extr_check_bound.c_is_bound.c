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
struct fdlist {TYPE_1__* nconf; struct fdlist* next; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  nc_netid; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_bound (struct fdlist*,char*) ; 
 struct fdlist* fdhead ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bool_t
is_bound(char *netid, char *uaddr)
{
	struct fdlist *fdl;

	for (fdl = fdhead; fdl; fdl = fdl->next)
		if (strcmp(fdl->nconf->nc_netid, netid) == 0)
			break;
	if (fdl == NULL)
		return (TRUE);
	return (check_bound(fdl, uaddr));
}
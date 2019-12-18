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
struct ifnet {char const* if_dname; int if_dunit; int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int IF_DUNIT_NONE ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
if_initname(struct ifnet *ifp, const char *name, int unit)
{
	ifp->if_dname = name;
	ifp->if_dunit = unit;
	if (unit != IF_DUNIT_NONE)
		snprintf(ifp->if_xname, IFNAMSIZ, "%s%d", name, unit);
	else
		strlcpy(ifp->if_xname, name, IFNAMSIZ);
}
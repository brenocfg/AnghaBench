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
struct sort_mods {scalar_t__ Vflag; scalar_t__ Rflag; scalar_t__ Mflag; scalar_t__ gflag; scalar_t__ hflag; scalar_t__ nflag; } ;
typedef  int /*<<< orphan*/  cmpcoll_t ;

/* Variables and functions */
 int /*<<< orphan*/  gnumcoll ; 
 int /*<<< orphan*/  hnumcoll ; 
 int /*<<< orphan*/  monthcoll ; 
 int /*<<< orphan*/  numcoll ; 
 int /*<<< orphan*/  randomcoll ; 
 int /*<<< orphan*/  versioncoll ; 
 int /*<<< orphan*/  wstrcoll ; 

cmpcoll_t
get_sort_func(struct sort_mods *sm)
{

	if (sm->nflag)
		return (numcoll);
	else if (sm->hflag)
		return (hnumcoll);
	else if (sm->gflag)
		return (gnumcoll);
	else if (sm->Mflag)
		return (monthcoll);
	else if (sm->Rflag)
		return (randomcoll);
	else if (sm->Vflag)
		return (versioncoll);
	else
		return (wstrcoll);
}
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
struct libalias {int dummy; } ;
struct ip {int /*<<< orphan*/  ip_id; int /*<<< orphan*/  ip_src; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 struct alias_link* FindFragmentPtr (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFragmentPtr (struct alias_link*,char**) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int /*<<< orphan*/  SetExpire (struct alias_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFragmentPtr (struct alias_link*,int /*<<< orphan*/ *) ; 

char           *
LibAliasGetFragment(struct libalias *la, char *ptr)
{
	struct alias_link *lnk;
	char *fptr;
	struct ip *pip;

	LIBALIAS_LOCK(la);
	pip = (struct ip *)ptr;
	lnk = FindFragmentPtr(la, pip->ip_src, pip->ip_id);
	if (lnk != NULL) {
		GetFragmentPtr(lnk, &fptr);
		SetFragmentPtr(lnk, NULL);
		SetExpire(lnk, 0);	/* Deletes link */
	} else		
		fptr = NULL;

	LIBALIAS_UNLOCK(la);
	return (fptr);
}
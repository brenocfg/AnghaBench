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
 struct alias_link* AddFragmentPtrLink (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int PKT_ALIAS_ERROR ; 
 int PKT_ALIAS_OK ; 
 int /*<<< orphan*/  SetFragmentPtr (struct alias_link*,char*) ; 

int
LibAliasSaveFragment(struct libalias *la, char *ptr)
{
	int iresult;
	struct alias_link *lnk;
	struct ip *pip;

	LIBALIAS_LOCK(la);
	pip = (struct ip *)ptr;
	lnk = AddFragmentPtrLink(la, pip->ip_src, pip->ip_id);
	iresult = PKT_ALIAS_ERROR;
	if (lnk != NULL) {
		SetFragmentPtr(lnk, ptr);
		iresult = PKT_ALIAS_OK;
	}
	LIBALIAS_UNLOCK(la);
	return (iresult);
}
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
struct alias_link {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int LINK_PARTIALLY_SPECIFIED ; 
 int LINK_PERMANENT ; 

int
LibAliasRedirectDynamic(struct libalias *la, struct alias_link *lnk)
{
	int res;

	LIBALIAS_LOCK(la);
	(void)la;

	if (lnk->flags & LINK_PARTIALLY_SPECIFIED)
		res = -1;
	else {
		lnk->flags &= ~LINK_PERMANENT;
		res = 0;
	}
	LIBALIAS_UNLOCK(la);
	return (res);
}
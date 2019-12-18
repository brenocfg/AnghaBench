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
struct libalias {int deleteAllLinks; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLink (struct alias_link*) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 

void
LibAliasRedirectDelete(struct libalias *la, struct alias_link *lnk)
{
/* This is a dangerous function to put in the API,
   because an invalid pointer can crash the program. */

	LIBALIAS_LOCK(la);
	la->deleteAllLinks = 1;
	DeleteLink(lnk);
	la->deleteAllLinks = 0;
	LIBALIAS_UNLOCK(la);
}
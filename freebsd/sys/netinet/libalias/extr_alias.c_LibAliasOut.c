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

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int LibAliasOutLocked (struct libalias*,char*,int,int) ; 

int
LibAliasOut(struct libalias *la, char *ptr, int maxpacketsize)
{
	int res;

	LIBALIAS_LOCK(la);
	res = LibAliasOutLocked(la, ptr, maxpacketsize, 1);
	LIBALIAS_UNLOCK(la);
	return (res);
}
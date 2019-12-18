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
struct libalias {unsigned int fireWallBaseNum; unsigned int fireWallNumNums; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 

void
LibAliasSetFWBase(struct libalias *la, unsigned int base, unsigned int num)
{

	LIBALIAS_LOCK(la);
#ifndef NO_FW_PUNCH
	la->fireWallBaseNum = base;
	la->fireWallNumNums = num;
#endif
	LIBALIAS_UNLOCK(la);
}
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

/* Variables and functions */
 int /*<<< orphan*/  AliasSctpTerm (struct libalias*) ; 
 int /*<<< orphan*/  CleanupAliasData (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_DESTROY (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct libalias*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UninitPacketAliasLog (struct libalias*) ; 
 int /*<<< orphan*/  UninitPunchFW (struct libalias*) ; 
 int /*<<< orphan*/  free (struct libalias*) ; 
 int /*<<< orphan*/  instancelist ; 

void
LibAliasUninit(struct libalias *la)
{

	LIBALIAS_LOCK(la);
#ifdef _KERNEL
	AliasSctpTerm(la);
#endif
	la->deleteAllLinks = 1;
	CleanupAliasData(la);
	la->deleteAllLinks = 0;
	UninitPacketAliasLog(la);
#ifndef NO_FW_PUNCH
	UninitPunchFW(la);
#endif
	LIST_REMOVE(la, instancelist);
	LIBALIAS_UNLOCK(la);
	LIBALIAS_LOCK_DESTROY(la);
	free(la);
}
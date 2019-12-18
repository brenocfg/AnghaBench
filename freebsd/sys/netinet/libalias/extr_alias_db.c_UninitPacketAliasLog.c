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
struct libalias {int /*<<< orphan*/  packetAliasMode; int /*<<< orphan*/ * logDesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  PKT_ALIAS_LOG ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
UninitPacketAliasLog(struct libalias *la)
{

	LIBALIAS_LOCK_ASSERT(la);
	if (la->logDesc) {
#ifdef _KERNEL
		free(la->logDesc);
#else
		fclose(la->logDesc);
#endif
		la->logDesc = NULL;
	}
	la->packetAliasMode &= ~PKT_ALIAS_LOG;
}
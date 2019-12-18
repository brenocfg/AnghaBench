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
struct puffs_kargs {int /*<<< orphan*/  pa_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUFFS_KFLAG_CACHE_FS_TTL ; 
 int /*<<< orphan*/  PUFFS_KFLAG_MASK ; 

__attribute__((used)) static void
fixkflag(struct puffs_kargs *kargs)
{

	kargs->pa_flags &= PUFFS_KFLAG_MASK;

	/*
	 * PUFFS_KFLAG_CACHE_FS_TTL require extended behavior
	 * from the filesystem for which we have no test right now.
	 */
	kargs->pa_flags &= ~PUFFS_KFLAG_CACHE_FS_TTL;
}
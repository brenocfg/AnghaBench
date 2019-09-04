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

/* Variables and functions */
 int REFRESH_IN_PORCELAIN ; 
 int /*<<< orphan*/  die_resolve_conflict (char*) ; 
 scalar_t__ refresh_cache (int) ; 

__attribute__((used)) static void refresh_cache_or_die(int refresh_flags)
{
	/*
	 * refresh_flags contains REFRESH_QUIET, so the only errors
	 * are for unmerged entries.
	 */
	if (refresh_cache(refresh_flags | REFRESH_IN_PORCELAIN))
		die_resolve_conflict("commit");
}
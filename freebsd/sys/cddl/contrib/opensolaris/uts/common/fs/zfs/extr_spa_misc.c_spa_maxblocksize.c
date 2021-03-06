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
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_FEATURE_LARGE_BLOCKS ; 
 int SPA_MAXBLOCKSIZE ; 
 int SPA_OLD_MAXBLOCKSIZE ; 
 scalar_t__ spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
spa_maxblocksize(spa_t *spa)
{
	if (spa_feature_is_enabled(spa, SPA_FEATURE_LARGE_BLOCKS))
		return (SPA_MAXBLOCKSIZE);
	else
		return (SPA_OLD_MAXBLOCKSIZE);
}
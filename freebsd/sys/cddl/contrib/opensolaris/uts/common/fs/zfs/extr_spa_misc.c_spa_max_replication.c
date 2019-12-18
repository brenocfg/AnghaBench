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
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_DVAS_PER_BP ; 
 scalar_t__ SPA_VERSION_DITTO_BLOCKS ; 
 int /*<<< orphan*/  spa_max_replication_override ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 

int
spa_max_replication(spa_t *spa)
{
	/*
	 * As of SPA_VERSION == SPA_VERSION_DITTO_BLOCKS, we are able to
	 * handle BPs with more than one DVA allocated.  Set our max
	 * replication level accordingly.
	 */
	if (spa_version(spa) < SPA_VERSION_DITTO_BLOCKS)
		return (1);
	return (MIN(SPA_DVAS_PER_BP, spa_max_replication_override));
}
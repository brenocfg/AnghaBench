#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  spa_load_guid; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */

uint64_t
spa_load_guid(spa_t *spa)
{
	/*
	 * This is a GUID that exists solely as a reference for the
	 * purposes of the arc.  It is generated at load time, and
	 * is never written to persistent storage.
	 */
	return (spa->spa_load_guid);
}
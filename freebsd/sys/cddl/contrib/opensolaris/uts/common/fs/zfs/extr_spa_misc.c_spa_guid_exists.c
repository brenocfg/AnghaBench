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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * spa_by_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
spa_guid_exists(uint64_t pool_guid, uint64_t device_guid)
{
	return (spa_by_guid(pool_guid, device_guid) != NULL);
}
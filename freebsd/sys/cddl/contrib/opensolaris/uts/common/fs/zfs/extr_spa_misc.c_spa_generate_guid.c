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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 scalar_t__ spa_get_random (unsigned long long) ; 
 scalar_t__ spa_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_guid_exists (scalar_t__,scalar_t__) ; 

uint64_t
spa_generate_guid(spa_t *spa)
{
	uint64_t guid = spa_get_random(-1ULL);

	if (spa != NULL) {
		while (guid == 0 || spa_guid_exists(spa_guid(spa), guid))
			guid = spa_get_random(-1ULL);
	} else {
		while (guid == 0 || spa_guid_exists(guid, 0))
			guid = spa_get_random(-1ULL);
	}

	return (guid);
}
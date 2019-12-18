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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 void* MAP_FAILED ; 
 scalar_t__ munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page ; 

__attribute__((used)) static void
map_check(void *map, int flag)
{

	if (flag != 0) {
		ATF_REQUIRE(map == MAP_FAILED);
		return;
	}

	ATF_REQUIRE(map != MAP_FAILED);
	ATF_REQUIRE(munmap(map, page) == 0);
}
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
 int MAP_ANON ; 
 void* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int minherit (void*,int /*<<< orphan*/ ,int) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page ; 

__attribute__((used)) static void *
makemap(int v, int f) {
	void *map = mmap(NULL, page, PROT_READ|PROT_WRITE,
	    MAP_SHARED|MAP_ANON, -1, 0);
	ATF_REQUIRE(map != MAP_FAILED);
	memset(map, v, page);
	if (f != 666)
		ATF_REQUIRE(minherit(map, page, f) == 0);
	else
		ATF_REQUIRE(minherit(map, page, f) == -1);
	return map;
}
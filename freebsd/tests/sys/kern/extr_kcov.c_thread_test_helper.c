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

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*) ; 
 scalar_t__ atomic_load_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
thread_test_helper(void *ptr)
{
	uint64_t *buf = ptr;

	atomic_store_64(&buf[0], 0);
	sleep(0);
	ATF_REQUIRE_MSG(atomic_load_64(&buf[0]) == 0,
	    "Records changed in blocked thread");

	return (NULL);
}
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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ munmap (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
common_tail(int fd, void *data)
{

	ATF_REQUIRE_MSG(munmap(data, PAGE_SIZE) == 0,
	    "Unable to unmap the kcov buffer");

	close(fd);
}
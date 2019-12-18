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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ex ; 
 int extent_alloc_subregion1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ret ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
h_alloc_subregion(u_long substart, u_long subend, u_long size,
    u_long alignment, u_long boundary, int expret, u_long expres)
{
	u_long result;

#define FAIL(fmt, ...) \
	atf_tc_fail("extent_alloc_subregion1(ex, %#lx, %#lx, %#lx, %#lx, 0, " \
	    "%#lx, 0, &result): " fmt, substart, subend, size, alignment, \
	    boundary, ##__VA_ARGS__)

	ret = extent_alloc_subregion1(ex, substart, subend, size,
	    alignment, 0, boundary, 0, &result);

	if (ret != expret)
		FAIL("%s", strerror(errno));

	if (expret == 0 && result != expres)
		FAIL("result should be: %#lx, got: %#lx", expres, result);
#undef FAIL
}
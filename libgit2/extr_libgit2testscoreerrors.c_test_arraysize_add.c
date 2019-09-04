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
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,size_t) ; 

__attribute__((used)) static int test_arraysize_add(size_t one, size_t two)
{
	size_t out;
	GIT_ERROR_CHECK_ALLOC_ADD(&out, one, two);
	return 0;
}
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
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_MULTIPLY (size_t*,size_t,size_t) ; 

__attribute__((used)) static int test_arraysize_multiply(size_t nelem, size_t size)
{
	size_t out;
	GIT_ERROR_CHECK_ALLOC_MULTIPLY(&out, nelem, size);
	return 0;
}
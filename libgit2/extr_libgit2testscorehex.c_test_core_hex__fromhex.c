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
 int /*<<< orphan*/  cl_assert (int) ; 
 int git__fromhex (char) ; 

void test_core_hex__fromhex(void)
{
	/* Passing cases */
	cl_assert(git__fromhex('0') == 0x0);
	cl_assert(git__fromhex('1') == 0x1);
	cl_assert(git__fromhex('3') == 0x3);
	cl_assert(git__fromhex('9') == 0x9);
	cl_assert(git__fromhex('A') == 0xa);
	cl_assert(git__fromhex('C') == 0xc);
	cl_assert(git__fromhex('F') == 0xf);
	cl_assert(git__fromhex('a') == 0xa);
	cl_assert(git__fromhex('c') == 0xc);
	cl_assert(git__fromhex('f') == 0xf);

	/* Failing cases */
	cl_assert(git__fromhex('g') == -1);
	cl_assert(git__fromhex('z') == -1);
	cl_assert(git__fromhex('X') == -1);
}
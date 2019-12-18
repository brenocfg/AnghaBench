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
typedef  int /*<<< orphan*/  delta ;
typedef  int /*<<< orphan*/  base ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_delta_apply (void**,size_t*,unsigned char*,int,unsigned char*,int) ; 

void test_delta_apply__read_at_off(void)
{
	unsigned char base[16] = { 0 }, delta[] = { 0x10, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00 };
	void *out;
	size_t outlen;

	cl_git_fail(git_delta_apply(&out, &outlen, base, sizeof(base), delta, sizeof(delta)));
}
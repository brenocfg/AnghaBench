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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int ffs_fstest_delfs (int /*<<< orphan*/  const*,void*) ; 

int
p2k_ffs_fstest_delfs(const atf_tc_t *tc, void *arg)
{

	return ffs_fstest_delfs(tc, arg);
}
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
 scalar_t__ p_fsync__cnt ; 
 int /*<<< orphan*/  write_object_to_loose_odb (int) ; 

void test_odb_loose__fsync_obeys_odb_option(void)
{
	write_object_to_loose_odb(1);
	cl_assert(p_fsync__cnt > 0);
}
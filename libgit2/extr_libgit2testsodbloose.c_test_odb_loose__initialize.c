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
 int /*<<< orphan*/  GIT_OBJECT_DIR_MODE ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ p_fsync__cnt ; 
 int /*<<< orphan*/  p_mkdir (char*,int /*<<< orphan*/ ) ; 

void test_odb_loose__initialize(void)
{
	p_fsync__cnt = 0;
	cl_must_pass(p_mkdir("test-objects", GIT_OBJECT_DIR_MODE));
}
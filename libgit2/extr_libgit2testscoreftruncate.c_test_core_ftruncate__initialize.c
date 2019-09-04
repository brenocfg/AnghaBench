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
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  p_open (int /*<<< orphan*/ ,int,int) ; 

void test_core_ftruncate__initialize(void)
{
	if (!cl_is_env_set("GITTEST_INVASIVE_FS_SIZE"))
		cl_skip();

	cl_must_pass((fd = p_open(filename, O_CREAT | O_RDWR, 0644)));
}
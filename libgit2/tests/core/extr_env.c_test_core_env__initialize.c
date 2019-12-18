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
 int NUM_VARS ; 
 int /*<<< orphan*/  cl_getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * env_save ; 
 int /*<<< orphan*/ * env_vars ; 

void test_core_env__initialize(void)
{
	int i;
	for (i = 0; i < NUM_VARS; ++i)
		env_save[i] = cl_getenv(env_vars[i]);
}
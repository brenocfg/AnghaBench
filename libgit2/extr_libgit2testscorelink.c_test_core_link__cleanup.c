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

void test_core_link__cleanup(void)
{
#ifdef GIT_WIN32
	RemoveDirectory("lstat_junction");
	RemoveDirectory("lstat_dangling");
	RemoveDirectory("lstat_dangling_dir");
	RemoveDirectory("lstat_dangling_junction");

	RemoveDirectory("stat_junction");
	RemoveDirectory("stat_dangling");
	RemoveDirectory("stat_dangling_dir");
	RemoveDirectory("stat_dangling_junction");
#endif
}
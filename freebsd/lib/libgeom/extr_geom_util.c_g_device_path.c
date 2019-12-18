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
 char* g_device_path_open (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *
g_device_path(const char *devpath)
{
	return (g_device_path_open(devpath, NULL, 0));
}
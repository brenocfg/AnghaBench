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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vu_cmdline_get_device ; 
 int /*<<< orphan*/  vu_cmdline_parent ; 
 scalar_t__ vu_cmdline_parent_registered ; 

__attribute__((used)) static int vu_cmdline_get(char *buffer, const struct kernel_param *kp)
{
	buffer[0] = '\0';
	if (vu_cmdline_parent_registered)
		device_for_each_child(&vu_cmdline_parent, buffer,
				      vu_cmdline_get_device);
	return strlen(buffer) + 1;
}
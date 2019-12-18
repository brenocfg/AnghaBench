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
struct ptdump_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char const*,int,int /*<<< orphan*/ *,struct ptdump_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptdump_fops ; 

void ptdump_debugfs_register(struct ptdump_info *info, const char *name)
{
	debugfs_create_file(name, 0400, NULL, info, &ptdump_fops);
}
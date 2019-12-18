#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aoedev {int /*<<< orphan*/  debugfs; TYPE_1__* gd; } ;
struct TYPE_2__ {char* disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/ * aoe_debugfs_dir ; 
 int /*<<< orphan*/  aoe_debugfs_fops ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ *,struct aoedev*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
aoedisk_add_debugfs(struct aoedev *d)
{
	char *p;

	if (aoe_debugfs_dir == NULL)
		return;
	p = strchr(d->gd->disk_name, '/');
	if (p == NULL)
		p = d->gd->disk_name;
	else
		p++;
	BUG_ON(*p == '\0');
	d->debugfs = debugfs_create_file(p, 0444, aoe_debugfs_dir, d,
					 &aoe_debugfs_fops);
}
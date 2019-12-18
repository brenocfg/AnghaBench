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
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct be_mountcheck_info {int /*<<< orphan*/  name; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_is_mounted (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static int
be_mountcheck_cb(zfs_handle_t *zfs_hdl, void *data)
{
	struct be_mountcheck_info *info;
	char *mountpoint;

	if (data == NULL)
		return (1);
	info = (struct be_mountcheck_info *)data;
	if (!zfs_is_mounted(zfs_hdl, &mountpoint))
		return (0);
	if (strcmp(mountpoint, info->path) == 0) {
		info->name = strdup(zfs_get_name(zfs_hdl));
		free(mountpoint);
		return (1);
	}
	free(mountpoint);
	return (0);
}
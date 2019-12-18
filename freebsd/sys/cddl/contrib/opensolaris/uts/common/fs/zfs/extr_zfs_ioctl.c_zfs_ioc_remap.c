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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dmu_objset_remap_indirects (char const*) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static int
zfs_ioc_remap(const char *fsname, nvlist_t *innvl, nvlist_t *outnvl)
{
	if (strchr(fsname, '@') ||
	    strchr(fsname, '%'))
		return (SET_ERROR(EINVAL));

	return (dmu_objset_remap_indirects(fsname));
}
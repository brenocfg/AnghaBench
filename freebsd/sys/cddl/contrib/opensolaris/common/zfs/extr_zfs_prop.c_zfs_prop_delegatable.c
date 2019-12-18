#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pd_attr; } ;
typedef  TYPE_1__ zprop_desc_t ;
typedef  size_t zfs_prop_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 scalar_t__ PROP_READONLY ; 
 size_t ZFS_PROP_MLSLABEL ; 
 TYPE_1__* zfs_prop_table ; 

boolean_t
zfs_prop_delegatable(zfs_prop_t prop)
{
	zprop_desc_t *pd = &zfs_prop_table[prop];

	/* The mlslabel property is never delegatable. */
	if (prop == ZFS_PROP_MLSLABEL)
		return (B_FALSE);

	return (pd->pd_attr != PROP_READONLY);
}
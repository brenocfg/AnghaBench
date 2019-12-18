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
typedef  int /*<<< orphan*/  zpool_prop_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_TYPE_POOL ; 
 int /*<<< orphan*/  zprop_name_to_prop (char const*,int /*<<< orphan*/ ) ; 

zpool_prop_t
zpool_name_to_prop(const char *propname)
{
	return (zprop_name_to_prop(propname, ZFS_TYPE_POOL));
}
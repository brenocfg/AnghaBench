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
typedef  size_t zfs_prop_t ;
struct TYPE_2__ {scalar_t__ pd_proptype; } ;

/* Variables and functions */
 scalar_t__ PROP_TYPE_INDEX ; 
 scalar_t__ PROP_TYPE_STRING ; 
 TYPE_1__* zfs_prop_table ; 

int
zfs_prop_is_string(zfs_prop_t prop)
{
	return (zfs_prop_table[prop].pd_proptype == PROP_TYPE_STRING ||
	    zfs_prop_table[prop].pd_proptype == PROP_TYPE_INDEX);
}
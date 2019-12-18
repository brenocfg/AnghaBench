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
typedef  int boolean_t ;
struct TYPE_2__ {scalar_t__ pd_attr; } ;

/* Variables and functions */
 scalar_t__ PROP_INHERIT ; 
 scalar_t__ PROP_ONETIME ; 
 TYPE_1__* zfs_prop_table ; 

boolean_t
zfs_prop_inheritable(zfs_prop_t prop)
{
	return (zfs_prop_table[prop].pd_attr == PROP_INHERIT ||
	    zfs_prop_table[prop].pd_attr == PROP_ONETIME);
}
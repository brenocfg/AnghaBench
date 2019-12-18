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
 scalar_t__ get_dataset_depth (char const*) ; 
 scalar_t__ zfs_max_dataset_nesting ; 

int
dataset_nestcheck(const char *path)
{
	return ((get_dataset_depth(path) < zfs_max_dataset_nesting) ? 0 : -1);
}
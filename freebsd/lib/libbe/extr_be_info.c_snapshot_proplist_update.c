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
typedef  int /*<<< orphan*/  prop_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  prop_list_builder_cb ; 
 int zfs_iter_snapshots_sorted (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snapshot_proplist_update(zfs_handle_t *hdl, prop_data_t *data)
{

	return (zfs_iter_snapshots_sorted(hdl, prop_list_builder_cb, data,
	    0, 0));
}
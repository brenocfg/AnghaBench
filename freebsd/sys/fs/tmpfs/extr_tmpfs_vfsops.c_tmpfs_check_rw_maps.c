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
struct tmpfs_check_rw_maps_arg {int found; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tmpfs_all_rw_maps (struct mount*,int /*<<< orphan*/ ,struct tmpfs_check_rw_maps_arg*) ; 
 int /*<<< orphan*/  tmpfs_check_rw_maps_cb ; 

__attribute__((used)) static bool
tmpfs_check_rw_maps(struct mount *mp)
{
	struct tmpfs_check_rw_maps_arg ca;

	ca.found = false;
	tmpfs_all_rw_maps(mp, tmpfs_check_rw_maps_cb, &ca);
	return (ca.found);
}
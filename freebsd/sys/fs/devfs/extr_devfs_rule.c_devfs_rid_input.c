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
struct devfs_mount {int /*<<< orphan*/  dm_ruleset; } ;
typedef  int /*<<< orphan*/  devfs_rid ;

/* Variables and functions */
 int /*<<< orphan*/  mkrid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rid2rn (int /*<<< orphan*/ ) ; 
 scalar_t__ rid2rsn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static devfs_rid
devfs_rid_input(devfs_rid rid, struct devfs_mount *dm)
{

	if (rid2rsn(rid) == 0)
		return (mkrid(dm->dm_ruleset, rid2rn(rid)));
	else
		return (rid);
}
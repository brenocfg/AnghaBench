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
struct devfs_rule {scalar_t__ dr_magic; int /*<<< orphan*/  dr_id; } ;
struct devfs_mount {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEVFS_MAGIC ; 
 int ERPCMISMATCH ; 
 int /*<<< orphan*/  devfs_rid_input (int /*<<< orphan*/ ,struct devfs_mount*) ; 

__attribute__((used)) static int
devfs_rule_input(struct devfs_rule *dr, struct devfs_mount *dm)
{

	if (dr->dr_magic != DEVFS_MAGIC)
		return (ERPCMISMATCH);
	dr->dr_id = devfs_rid_input(dr->dr_id, dm);
	return (0);
}
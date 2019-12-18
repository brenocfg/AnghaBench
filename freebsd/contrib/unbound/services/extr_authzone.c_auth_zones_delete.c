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
struct auth_zones {int /*<<< orphan*/  xtree; int /*<<< orphan*/  ztree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_xfer_del ; 
 int /*<<< orphan*/  auth_zone_del ; 
 int /*<<< orphan*/  free (struct auth_zones*) ; 
 int /*<<< orphan*/  lock_rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void auth_zones_delete(struct auth_zones* az)
{
	if(!az) return;
	lock_rw_destroy(&az->lock);
	traverse_postorder(&az->ztree, auth_zone_del, NULL);
	traverse_postorder(&az->xtree, auth_xfer_del, NULL);
	free(az);
}
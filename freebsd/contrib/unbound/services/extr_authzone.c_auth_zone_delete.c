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
struct auth_zone {struct auth_zone* zonefile; struct auth_zone* name; int /*<<< orphan*/  data; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_data_del ; 
 int /*<<< orphan*/  free (struct auth_zone*) ; 
 int /*<<< orphan*/  lock_rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
auth_zone_delete(struct auth_zone* z)
{
	if(!z) return;
	lock_rw_destroy(&z->lock);
	traverse_postorder(&z->data, auth_data_del, NULL);
	free(z->name);
	free(z->zonefile);
	free(z);
}
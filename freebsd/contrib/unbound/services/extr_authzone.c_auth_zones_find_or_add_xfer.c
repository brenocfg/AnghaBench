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
struct auth_zones {int dummy; } ;
struct auth_zone {int /*<<< orphan*/  dclass; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct auth_xfer {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct auth_xfer* auth_xfer_create (struct auth_zones*,struct auth_zone*) ; 
 struct auth_xfer* auth_xfer_find (struct auth_zones*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct auth_xfer*
auth_zones_find_or_add_xfer(struct auth_zones* az, struct auth_zone* z)
{
	struct auth_xfer* x;
	x = auth_xfer_find(az, z->name, z->namelen, z->dclass);
	if(!x) {
		/* not found, create the zone */
		x = auth_xfer_create(az, z);
	} else {
		lock_basic_lock(&x->lock);
	}
	return x;
}
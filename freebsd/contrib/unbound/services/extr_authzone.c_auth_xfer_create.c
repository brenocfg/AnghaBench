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
struct auth_zones {int /*<<< orphan*/  xtree; } ;
struct auth_zone {int dummy; } ;
struct auth_xfer {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 struct auth_xfer* auth_xfer_new (struct auth_zone*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct auth_xfer*
auth_xfer_create(struct auth_zones* az, struct auth_zone* z)
{
	struct auth_xfer* xfr;

	/* malloc it */
	xfr = auth_xfer_new(z);
	if(!xfr) {
		log_err("malloc failure");
		return NULL;
	}
	/* insert in tree */
	(void)rbtree_insert(&az->xtree, &xfr->node);
	return xfr;
}
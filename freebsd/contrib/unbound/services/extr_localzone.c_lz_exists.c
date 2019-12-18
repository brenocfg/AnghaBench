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
struct local_zones {int /*<<< orphan*/  lock; int /*<<< orphan*/  ztree; } ;
struct TYPE_2__ {struct local_zone* key; } ;
struct local_zone {int /*<<< orphan*/  name; TYPE_1__ node; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  namelen; int /*<<< orphan*/  dclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/  parse_dname (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
lz_exists(struct local_zones* zones, const char* name)
{
	struct local_zone z;
	z.node.key = &z;
	z.dclass = LDNS_RR_CLASS_IN;
	if(!parse_dname(name, &z.name, &z.namelen, &z.namelabs)) {
		log_err("bad name %s", name);
		return 0;
	}
	lock_rw_rdlock(&zones->lock);
	if(rbtree_search(&zones->ztree, &z.node)) {
		lock_rw_unlock(&zones->lock);
		free(z.name);
		return 1;
	}
	lock_rw_unlock(&zones->lock);
	free(z.name);
	return 0;
}
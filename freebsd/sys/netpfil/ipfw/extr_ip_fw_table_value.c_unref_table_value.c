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
typedef  size_t uint32_t ;
struct table_value {scalar_t__ refcnt; } ;
struct table_val_link {int /*<<< orphan*/  no; } ;
struct namedobj_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  free (struct table_val_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_del (struct namedobj_instance*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipfw_objhash_free_idx (struct namedobj_instance*,size_t) ; 
 scalar_t__ ipfw_objhash_lookup_kidx (struct namedobj_instance*,size_t) ; 

__attribute__((used)) static void
unref_table_value(struct namedobj_instance *vi, struct table_value *pval,
    uint32_t kidx)
{
	struct table_val_link *ptvl;

	KASSERT(pval[kidx].refcnt > 0, ("Refcount is 0 on kidx %d", kidx));
	if (--pval[kidx].refcnt > 0)
		return;

	/* Last reference, delete item */
	ptvl = (struct table_val_link *)ipfw_objhash_lookup_kidx(vi, kidx);
	KASSERT(ptvl != NULL, ("lookup on value kidx %d failed", kidx));
	ipfw_objhash_del(vi, &ptvl->no);
	ipfw_objhash_free_idx(vi, kidx);
	free(ptvl, M_IPFW);
}
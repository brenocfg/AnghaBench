#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_8__ {int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_matched; int /*<<< orphan*/  p_setname; } ;
typedef  TYPE_2__ perm_set_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int ZFS_MAX_DELEG_NAME ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_deleg_whokey (char*,char,char,void*) ; 

__attribute__((used)) static int
dsl_load_sets(objset_t *mos, uint64_t zapobj,
    char type, char checkflag, void *valp, avl_tree_t *avl)
{
	zap_cursor_t zc;
	zap_attribute_t za;
	perm_set_t *permnode;
	avl_index_t idx;
	uint64_t jumpobj;
	int error;
	char whokey[ZFS_MAX_DELEG_NAME];

	zfs_deleg_whokey(whokey, type, checkflag, valp);

	error = zap_lookup(mos, zapobj, whokey, 8, 1, &jumpobj);
	if (error != 0)
		return (error);

	for (zap_cursor_init(&zc, mos, jumpobj);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		permnode = kmem_alloc(sizeof (perm_set_t), KM_SLEEP);
		(void) strlcpy(permnode->p_setname, za.za_name,
		    sizeof (permnode->p_setname));
		permnode->p_matched = B_FALSE;

		if (avl_find(avl, permnode, &idx) == NULL) {
			avl_insert(avl, permnode, idx);
		} else {
			kmem_free(permnode, sizeof (perm_set_t));
		}
	}
	zap_cursor_fini(&zc);
	return (0);
}
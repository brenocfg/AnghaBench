#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * v_object; int /*<<< orphan*/ * v_mount; } ;
typedef  TYPE_1__ vnode_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct sf_buf {int dummy; } ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_READ_PREFETCH ; 
 int PAGEMASK ; 
 int PAGEOFFSET ; 
 scalar_t__ PAGESIZE ; 
 int UIO_NOCOPY ; 
 int /*<<< orphan*/  dmu_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imin (scalar_t__,int) ; 
 int /*<<< orphan*/ * page_busy (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  page_unbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_pip_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_object_pip_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_map_page (int /*<<< orphan*/ *,struct sf_buf**) ; 
 int /*<<< orphan*/  zfs_unmap_page (struct sf_buf*) ; 
 int /*<<< orphan*/  zfs_vmobject_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_vmobject_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_pages(vnode_t *vp, int64_t start, int len, objset_t *os, uint64_t oid,
    int segflg, dmu_tx_t *tx)
{
	vm_object_t obj;
	struct sf_buf *sf;
	caddr_t va;
	int off;

	ASSERT(segflg != UIO_NOCOPY);
	ASSERT(vp->v_mount != NULL);
	obj = vp->v_object;
	ASSERT(obj != NULL);

	off = start & PAGEOFFSET;
	zfs_vmobject_wlock(obj);
	vm_object_pip_add(obj, 1);
	for (start &= PAGEMASK; len > 0; start += PAGESIZE) {
		vm_page_t pp;
		int nbytes = imin(PAGESIZE - off, len);

		if ((pp = page_busy(vp, start, off, nbytes)) != NULL) {
			zfs_vmobject_wunlock(obj);

			va = zfs_map_page(pp, &sf);
			(void) dmu_read(os, oid, start+off, nbytes,
			    va+off, DMU_READ_PREFETCH);;
			zfs_unmap_page(sf);

			zfs_vmobject_wlock(obj);
			page_unbusy(pp);
		}
		len -= nbytes;
		off = 0;
	}
	vm_object_pip_wakeup(obj);
	zfs_vmobject_wunlock(obj);
}
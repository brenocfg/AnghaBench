#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_13__ {int /*<<< orphan*/ * v_object; int /*<<< orphan*/ * v_mount; } ;
typedef  TYPE_2__ vnode_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct TYPE_14__ {int uio_loffset; } ;
typedef  TYPE_3__ uio_t ;
typedef  scalar_t__ uint64_t ;
struct sf_buf {int dummy; } ;
typedef  int int64_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int PAGEMASK ; 
 int PAGEOFFSET ; 
 scalar_t__ PAGESIZE ; 
 int /*<<< orphan*/  UIO_READ ; 
 TYPE_1__* VTOZ (TYPE_2__*) ; 
 int dmu_read_uio_dbuf (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  page_unwire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_wire (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sa_get_db (int /*<<< orphan*/ ) ; 
 int uiomove (scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int vn_io_fault_uiomove (scalar_t__,scalar_t__,TYPE_3__*) ; 
 scalar_t__ zfs_map_page (int /*<<< orphan*/ ,struct sf_buf**) ; 
 int /*<<< orphan*/  zfs_unmap_page (struct sf_buf*) ; 
 int /*<<< orphan*/  zfs_vmobject_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_vmobject_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mappedread(vnode_t *vp, int nbytes, uio_t *uio)
{
	znode_t *zp = VTOZ(vp);
	vm_object_t obj;
	int64_t start;
	caddr_t va;
	int len = nbytes;
	int off;
	int error = 0;

	ASSERT(vp->v_mount != NULL);
	obj = vp->v_object;
	ASSERT(obj != NULL);

	start = uio->uio_loffset;
	off = start & PAGEOFFSET;
	zfs_vmobject_wlock(obj);
	for (start &= PAGEMASK; len > 0; start += PAGESIZE) {
		vm_page_t pp;
		uint64_t bytes = MIN(PAGESIZE - off, len);

		if (pp = page_wire(vp, start)) {
			struct sf_buf *sf;
			caddr_t va;

			zfs_vmobject_wunlock(obj);
			va = zfs_map_page(pp, &sf);
#ifdef illumos
			error = uiomove(va + off, bytes, UIO_READ, uio);
#else
			error = vn_io_fault_uiomove(va + off, bytes, uio);
#endif
			zfs_unmap_page(sf);
			zfs_vmobject_wlock(obj);
			page_unwire(pp);
		} else {
			zfs_vmobject_wunlock(obj);
			error = dmu_read_uio_dbuf(sa_get_db(zp->z_sa_hdl),
			    uio, bytes);
			zfs_vmobject_wlock(obj);
		}
		len -= bytes;
		off = 0;
		if (error)
			break;
	}
	zfs_vmobject_wunlock(obj);
	return (error);
}
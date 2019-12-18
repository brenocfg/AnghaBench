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
struct rsocket {int iomap_pending; int /*<<< orphan*/  map_lock; int /*<<< orphan*/  iomap_list; int /*<<< orphan*/  iomap_queue; TYPE_1__* cm_id; } ;
struct rs_iomap_mr {int index; int offset; int /*<<< orphan*/  entry; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  mr; } ;
typedef  int off_t ;
struct TYPE_2__ {int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int IBV_ACCESS_LOCAL_WRITE ; 
 int IBV_ACCESS_REMOTE_WRITE ; 
 int PROT_NONE ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 struct rs_iomap_mr* calloc (int,int) ; 
 int /*<<< orphan*/  dlist_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct rs_iomap_mr*) ; 
 int /*<<< orphan*/  ibv_reg_mr (int /*<<< orphan*/ ,void*,size_t,int) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_at (int /*<<< orphan*/ *,int) ; 
 struct rs_iomap_mr* rs_get_iomap_mr (struct rsocket*) ; 

off_t riomap(int socket, void *buf, size_t len, int prot, int flags, off_t offset)
{
	struct rsocket *rs;
	struct rs_iomap_mr *iomr;
	int access = IBV_ACCESS_LOCAL_WRITE;

	rs = idm_at(&idm, socket);
	if (!rs->cm_id->pd || (prot & ~(PROT_WRITE | PROT_NONE)))
		return ERR(EINVAL);

	fastlock_acquire(&rs->map_lock);
	if (prot & PROT_WRITE) {
		iomr = rs_get_iomap_mr(rs);
		access |= IBV_ACCESS_REMOTE_WRITE;
	} else {
		iomr = calloc(1, sizeof(*iomr));
		iomr->index = -1;
	}
	if (!iomr) {
		offset = ERR(ENOMEM);
		goto out;
	}

	iomr->mr = ibv_reg_mr(rs->cm_id->pd, buf, len, access);
	if (!iomr->mr) {
		if (iomr->index < 0)
			free(iomr);
		offset = -1;
		goto out;
	}

	if (offset == -1)
		offset = (uintptr_t) buf;
	iomr->offset = offset;
	atomic_store(&iomr->refcnt, 1);

	if (iomr->index >= 0) {
		dlist_insert_tail(&iomr->entry, &rs->iomap_queue);
		rs->iomap_pending = 1;
	} else {
		dlist_insert_tail(&iomr->entry, &rs->iomap_list);
	}
out:
	fastlock_release(&rs->map_lock);
	return offset;
}
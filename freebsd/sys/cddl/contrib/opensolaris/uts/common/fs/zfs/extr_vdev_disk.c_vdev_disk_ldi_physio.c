#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/ * ldi_handle_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_7__ {void* b_addr; } ;
struct TYPE_8__ {int b_flags; size_t b_bcount; size_t b_bufsize; scalar_t__ b_resid; int /*<<< orphan*/  b_lblkno; TYPE_1__ b_un; } ;
typedef  TYPE_2__ buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_BUSY ; 
 int B_FAILFAST ; 
 int B_NOCACHE ; 
 int B_READ ; 
 int B_WRITE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int biowait (TYPE_2__*) ; 
 int /*<<< orphan*/  freerbuf (TYPE_2__*) ; 
 TYPE_2__* getrbuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtodb (int /*<<< orphan*/ ) ; 
 int ldi_strategy (int /*<<< orphan*/ *,TYPE_2__*) ; 

int
vdev_disk_ldi_physio(ldi_handle_t vd_lh, caddr_t data,
    size_t size, uint64_t offset, int flags)
{
	buf_t *bp;
	int error = 0;

	if (vd_lh == NULL)
		return (SET_ERROR(EINVAL));

	ASSERT(flags & B_READ || flags & B_WRITE);

	bp = getrbuf(KM_SLEEP);
	bp->b_flags = flags | B_BUSY | B_NOCACHE | B_FAILFAST;
	bp->b_bcount = size;
	bp->b_un.b_addr = (void *)data;
	bp->b_lblkno = lbtodb(offset);
	bp->b_bufsize = size;

	error = ldi_strategy(vd_lh, bp);
	ASSERT(error == 0);
	if ((error = biowait(bp)) == 0 && bp->b_resid != 0)
		error = SET_ERROR(EIO);
	freerbuf(bp);

	return (error);
}
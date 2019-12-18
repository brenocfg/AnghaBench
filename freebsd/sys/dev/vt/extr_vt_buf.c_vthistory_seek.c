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
struct TYPE_2__ {int tp_row; } ;
struct vt_buf {int vb_flags; int vb_roffset; int vb_curroffset; int vb_history_size; TYPE_1__ vb_scr_size; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int VBF_HISTORY_FULL ; 
 int VBF_SCROLL ; 
#define  VHS_CUR 130 
#define  VHS_END 129 
#define  VHS_SET 128 

int
vthistory_seek(struct vt_buf *vb, int offset, int whence)
{
	int diff, top, bottom, roffset;

	/* No scrolling if not enabled. */
	if ((vb->vb_flags & VBF_SCROLL) == 0) {
		if (vb->vb_roffset != vb->vb_curroffset) {
			vb->vb_roffset = vb->vb_curroffset;
			return (0xffff);
		}
		return (0); /* No changes */
	}

	/* "top" may be a negative integer. */
	bottom = vb->vb_curroffset;
	top = (vb->vb_flags & VBF_HISTORY_FULL) ?
	    bottom + vb->vb_scr_size.tp_row - vb->vb_history_size :
	    0;

	roffset = 0; /* Make gcc happy. */
	switch (whence) {
	case VHS_SET:
		if (offset < 0)
			offset = 0;
		roffset = top + offset;
		break;
	case VHS_CUR:
		/*
		 * Operate on copy of offset value, since it temporary
		 * can be bigger than amount of rows in buffer.
		 */
		roffset = vb->vb_roffset;
		if (roffset >= bottom + vb->vb_scr_size.tp_row)
			roffset -= vb->vb_history_size;

		roffset += offset;
		roffset = MAX(roffset, top);
		roffset = MIN(roffset, bottom);

		if (roffset < 0)
			roffset = vb->vb_history_size + roffset;

		break;
	case VHS_END:
		/* Go to current offset. */
		roffset = vb->vb_curroffset;
		break;
	}

	diff = vb->vb_roffset != roffset;
	vb->vb_roffset = roffset;

	return (diff);
}
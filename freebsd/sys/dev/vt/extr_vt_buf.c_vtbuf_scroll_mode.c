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
struct vt_buf {int vb_flags; int /*<<< orphan*/  vb_cursor; } ;

/* Variables and functions */
 int VBF_SCROLL ; 
 int /*<<< orphan*/  VTBUF_LOCK (struct vt_buf*) ; 
 int /*<<< orphan*/  VTBUF_UNLOCK (struct vt_buf*) ; 
 int /*<<< orphan*/  vtbuf_dirty_cell (struct vt_buf*,int /*<<< orphan*/ *) ; 

void
vtbuf_scroll_mode(struct vt_buf *vb, int yes)
{
	int oflags, nflags;

	VTBUF_LOCK(vb);
	oflags = vb->vb_flags;
	if (yes)
		vb->vb_flags |= VBF_SCROLL;
	else
		vb->vb_flags &= ~VBF_SCROLL;
	nflags = vb->vb_flags;

	if (oflags != nflags)
		vtbuf_dirty_cell(vb, &vb->vb_cursor);
	VTBUF_UNLOCK(vb);
}
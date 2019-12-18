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
typedef  int /*<<< orphan*/  term_pos_t ;
struct vt_window {int vw_flags; TYPE_1__* vw_device; int /*<<< orphan*/  vw_buf; int /*<<< orphan*/  vw_font; } ;
struct TYPE_2__ {int /*<<< orphan*/  vd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDF_INVALID ; 
 int VWF_SCROLL ; 
 int /*<<< orphan*/  vt_resume_flush_timer (struct vt_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_termsize (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vthistory_seek (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
vt_scroll(struct vt_window *vw, int offset, int whence)
{
	int diff;
	term_pos_t size;

	if ((vw->vw_flags & VWF_SCROLL) == 0)
		return;

	vt_termsize(vw->vw_device, vw->vw_font, &size);

	diff = vthistory_seek(&vw->vw_buf, offset, whence);
	if (diff)
		vw->vw_device->vd_flags |= VDF_INVALID;
	vt_resume_flush_timer(vw, 0);
}
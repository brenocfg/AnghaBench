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
struct TYPE_2__ {int tp_col; int /*<<< orphan*/  tp_row; } ;
struct vt_buf {int vb_history_size; TYPE_1__ vb_scr_size; int /*<<< orphan*/ * vb_buffer; int /*<<< orphan*/ ** vb_rows; } ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtbuf_init_rows(struct vt_buf *vb)
{
	int r;

	vb->vb_history_size = MAX(vb->vb_history_size, vb->vb_scr_size.tp_row);

	for (r = 0; r < vb->vb_history_size; r++)
		vb->vb_rows[r] = &vb->vb_buffer[r * vb->vb_scr_size.tp_col];
}
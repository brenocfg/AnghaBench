#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_4__ {TYPE_1__ tr_end; int /*<<< orphan*/  tr_begin; } ;
struct vt_buf {TYPE_2__ vb_dirtyrect; int /*<<< orphan*/  vb_scr_size; } ;

/* Variables and functions */

__attribute__((used)) static void
vtbuf_make_undirty(struct vt_buf *vb)
{

	vb->vb_dirtyrect.tr_begin = vb->vb_scr_size;
	vb->vb_dirtyrect.tr_end.tp_row = vb->vb_dirtyrect.tr_end.tp_col = 0;
}
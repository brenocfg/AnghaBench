#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_9__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_13__ {TYPE_5__ tr_end; TYPE_2__ tr_begin; } ;
typedef  TYPE_6__ term_rect_t ;
struct TYPE_10__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_8__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_11__ {TYPE_3__ tr_end; TYPE_1__ tr_begin; } ;
struct vt_buf {TYPE_4__ vb_dirtyrect; } ;

/* Variables and functions */

void
vtbuf_dirty(struct vt_buf *vb, const term_rect_t *area)
{

	if (vb->vb_dirtyrect.tr_begin.tp_row > area->tr_begin.tp_row)
		vb->vb_dirtyrect.tr_begin.tp_row = area->tr_begin.tp_row;
	if (vb->vb_dirtyrect.tr_begin.tp_col > area->tr_begin.tp_col)
		vb->vb_dirtyrect.tr_begin.tp_col = area->tr_begin.tp_col;
	if (vb->vb_dirtyrect.tr_end.tp_row < area->tr_end.tp_row)
		vb->vb_dirtyrect.tr_end.tp_row = area->tr_end.tp_row;
	if (vb->vb_dirtyrect.tr_end.tp_col < area->tr_end.tp_col)
		vb->vb_dirtyrect.tr_end.tp_col = area->tr_end.tp_col;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  term_char_t ;
struct TYPE_6__ {int tp_col; size_t tp_row; } ;
struct TYPE_5__ {int tp_col; size_t tp_row; } ;
struct TYPE_4__ {int tp_col; } ;
struct vt_buf {int vb_mark_last; TYPE_3__ vb_mark_end; TYPE_2__ vb_mark_start; TYPE_1__ vb_scr_size; int /*<<< orphan*/ ** vb_rows; } ;

/* Variables and functions */
 char TCHAR_CHARACTER (int /*<<< orphan*/ ) ; 
#define  VTB_MARK_END 134 
#define  VTB_MARK_EXTEND 133 
#define  VTB_MARK_MOVE 132 
#define  VTB_MARK_NONE 131 
#define  VTB_MARK_ROW 130 
#define  VTB_MARK_START 129 
#define  VTB_MARK_WORD 128 
 int /*<<< orphan*/  vtbuf_flush_mark (struct vt_buf*) ; 
 void* vtbuf_wth (struct vt_buf*,int) ; 

int
vtbuf_set_mark(struct vt_buf *vb, int type, int col, int row)
{
	term_char_t *r;
	int i;

	switch (type) {
	case VTB_MARK_END:	/* B1 UP */
		if (vb->vb_mark_last != VTB_MARK_MOVE)
			return (0);
		/* FALLTHROUGH */
	case VTB_MARK_MOVE:
	case VTB_MARK_EXTEND:
		vtbuf_flush_mark(vb); /* Clean old mark. */
		vb->vb_mark_end.tp_col = col;
		vb->vb_mark_end.tp_row = vtbuf_wth(vb, row);
		break;
	case VTB_MARK_START:
		vtbuf_flush_mark(vb); /* Clean old mark. */
		vb->vb_mark_start.tp_col = col;
		vb->vb_mark_start.tp_row = vtbuf_wth(vb, row);
		/* Start again, so clear end point. */
		vb->vb_mark_end.tp_col = col;
		vb->vb_mark_end.tp_row = vtbuf_wth(vb, row);
		break;
	case VTB_MARK_WORD:
		vtbuf_flush_mark(vb); /* Clean old mark. */
		vb->vb_mark_start.tp_row = vb->vb_mark_end.tp_row =
		    vtbuf_wth(vb, row);
		r = vb->vb_rows[vb->vb_mark_start.tp_row];
		for (i = col; i >= 0; i --) {
			if (TCHAR_CHARACTER(r[i]) == ' ') {
				vb->vb_mark_start.tp_col = i + 1;
				break;
			}
		}
		for (i = col; i < vb->vb_scr_size.tp_col; i ++) {
			if (TCHAR_CHARACTER(r[i]) == ' ') {
				vb->vb_mark_end.tp_col = i;
				break;
			}
		}
		if (vb->vb_mark_start.tp_col > vb->vb_mark_end.tp_col)
			vb->vb_mark_start.tp_col = vb->vb_mark_end.tp_col;
		break;
	case VTB_MARK_ROW:
		vtbuf_flush_mark(vb); /* Clean old mark. */
		vb->vb_mark_start.tp_col = 0;
		vb->vb_mark_end.tp_col = vb->vb_scr_size.tp_col;
		vb->vb_mark_start.tp_row = vb->vb_mark_end.tp_row =
		    vtbuf_wth(vb, row);
		break;
	case VTB_MARK_NONE:
		vb->vb_mark_last = type;
		/* FALLTHROUGH */
	default:
		/* panic? */
		return (0);
	}

	vb->vb_mark_last = type;
	/* Draw new marked region. */
	vtbuf_flush_mark(vb);
	return (1);
}
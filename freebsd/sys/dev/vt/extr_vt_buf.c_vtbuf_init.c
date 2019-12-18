#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tp_col; } ;
typedef  TYPE_1__ term_pos_t ;
typedef  int /*<<< orphan*/  term_char_t ;
struct vt_buf {int vb_history_size; int vb_flags; void* vb_rows; void* vb_buffer; TYPE_1__ vb_scr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VTBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int VBF_DEFAULT_HISTORY_SIZE ; 
 int VBF_STATIC ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vtbuf_init_early (struct vt_buf*) ; 

void
vtbuf_init(struct vt_buf *vb, const term_pos_t *p)
{
	int sz;

	vb->vb_scr_size = *p;
	vb->vb_history_size = VBF_DEFAULT_HISTORY_SIZE;

	if ((vb->vb_flags & VBF_STATIC) == 0) {
		sz = vb->vb_history_size * p->tp_col * sizeof(term_char_t);
		vb->vb_buffer = malloc(sz, M_VTBUF, M_WAITOK | M_ZERO);

		sz = vb->vb_history_size * sizeof(term_char_t *);
		vb->vb_rows = malloc(sz, M_VTBUF, M_WAITOK | M_ZERO);
	}

	vtbuf_init_early(vb);
}
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
typedef  int /*<<< orphan*/  term_rect_t ;
struct vt_buf {int /*<<< orphan*/  vb_dirtyrect; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtbuf_make_undirty (struct vt_buf*) ; 

void
vtbuf_undirty(struct vt_buf *vb, term_rect_t *r)
{

	*r = vb->vb_dirtyrect;
	vtbuf_make_undirty(vb);
}
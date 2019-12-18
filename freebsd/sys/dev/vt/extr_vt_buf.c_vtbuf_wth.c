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
struct vt_buf {int vb_roffset; int vb_history_size; } ;

/* Variables and functions */

__attribute__((used)) static int
vtbuf_wth(const struct vt_buf *vb, int row)
{

	return ((vb->vb_roffset + row) % vb->vb_history_size);
}
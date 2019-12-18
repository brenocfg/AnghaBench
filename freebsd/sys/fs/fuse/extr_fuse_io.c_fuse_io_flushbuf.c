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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int vn_fsync_buf (struct vnode*,int) ; 

int
fuse_io_flushbuf(struct vnode *vp, int waitfor, struct thread *td)
{

	return (vn_fsync_buf(vp, waitfor));
}
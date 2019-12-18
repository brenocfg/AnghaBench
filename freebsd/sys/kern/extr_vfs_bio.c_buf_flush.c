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
struct bufdomain {int dummy; } ;

/* Variables and functions */
 int flushbufqueues (struct vnode*,struct bufdomain*,int,int) ; 

__attribute__((used)) static int
buf_flush(struct vnode *vp, struct bufdomain *bd, int target)
{
	int flushed;

	flushed = flushbufqueues(vp, bd, target, 0);
	if (flushed == 0) {
		/*
		 * Could not find any buffers without rollback
		 * dependencies, so just write the first one
		 * in the hopes of eventually making progress.
		 */
		if (vp != NULL && target > 2)
			target /= 2;
		flushbufqueues(vp, bd, target, 1);
	}
	return (flushed);
}
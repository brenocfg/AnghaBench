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
typedef  int daddr_t ;

/* Variables and functions */
 int cluster_wbuild (struct vnode*,long,int,int,int) ; 
 int write_behind ; 

__attribute__((used)) static __inline int
cluster_wbuild_wb(struct vnode *vp, long size, daddr_t start_lbn, int len,
    int gbflags)
{
	int r = 0;

	switch (write_behind) {
	case 2:
		if (start_lbn < len)
			break;
		start_lbn -= len;
		/* FALLTHROUGH */
	case 1:
		r = cluster_wbuild(vp, size, start_lbn, len, gbflags);
		/* FALLTHROUGH */
	default:
		/* FALLTHROUGH */
		break;
	}
	return(r);
}
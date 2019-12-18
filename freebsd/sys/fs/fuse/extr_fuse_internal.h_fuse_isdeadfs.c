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
struct fuse_data {int dataflags; } ;

/* Variables and functions */
 int FSESS_DEAD ; 
 struct fuse_data* fuse_get_mpdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

__attribute__((used)) static inline bool
fuse_isdeadfs(struct vnode *vp)
{
	struct fuse_data *data = fuse_get_mpdata(vnode_mount(vp));

	return (data->dataflags & FSESS_DEAD);
}
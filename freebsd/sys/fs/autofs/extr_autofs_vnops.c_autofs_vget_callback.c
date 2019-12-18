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
struct mount {int dummy; } ;

/* Variables and functions */
 int autofs_node_vn (void*,struct mount*,int,struct vnode**) ; 

__attribute__((used)) static int
autofs_vget_callback(struct mount *mp, void *arg, int flags,
    struct vnode **vpp)
{


	return (autofs_node_vn(arg, mp, flags, vpp));
}
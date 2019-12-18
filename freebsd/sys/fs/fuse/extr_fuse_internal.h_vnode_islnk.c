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
struct vnode {scalar_t__ v_type; } ;

/* Variables and functions */
 scalar_t__ VLNK ; 

__attribute__((used)) static inline bool
vnode_islnk(struct vnode *vp)
{
	return (vp->v_type == VLNK);
}
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
struct null_node {int /*<<< orphan*/  null_lowervp; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_destroy_proto (struct vnode*,void*) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
null_insmntque_dtr(struct vnode *vp, void *xp)
{

	vput(((struct null_node *)xp)->null_lowervp);
	null_destroy_proto(vp, xp);
}
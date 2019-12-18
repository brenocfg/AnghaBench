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

/* Variables and functions */
 int /*<<< orphan*/  VPUTX_VPUT ; 
 int /*<<< orphan*/  vputx (struct vnode*,int /*<<< orphan*/ ) ; 

void
vput(struct vnode *vp)
{

	vputx(vp, VPUTX_VPUT);
}
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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int vn_close1 (struct vnode*,int,struct ucred*,struct thread*,int) ; 

int
vn_close(struct vnode *vp, int flags, struct ucred *file_cred,
    struct thread *td)
{

	return (vn_close1(vp, flags, file_cred, td, false));
}
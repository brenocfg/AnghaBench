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
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREAD ; 
 int _fgetvp (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vnode**) ; 

int
fgetvp_read(struct thread *td, int fd, cap_rights_t *rightsp, struct vnode **vpp)
{

	return (_fgetvp(td, fd, FREAD, rightsp, vpp));
}
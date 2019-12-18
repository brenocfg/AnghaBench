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
struct export_fd_buf {scalar_t__ remainder; int /*<<< orphan*/ * fdp; int /*<<< orphan*/  flags; int /*<<< orphan*/  kif; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_SLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (int /*<<< orphan*/ *) ; 
 int export_kinfo_to_sb (struct export_fd_buf*) ; 
 int /*<<< orphan*/  export_vnode_to_kinfo (struct vnode*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
export_vnode_to_sb(struct vnode *vp, int fd, int fflags,
    struct export_fd_buf *efbuf)
{
	int error;

	if (efbuf->remainder == 0)
		return (0);
	if (efbuf->fdp != NULL)
		FILEDESC_SUNLOCK(efbuf->fdp);
	export_vnode_to_kinfo(vp, fd, fflags, &efbuf->kif, efbuf->flags);
	error = export_kinfo_to_sb(efbuf);
	if (efbuf->fdp != NULL)
		FILEDESC_SLOCK(efbuf->fdp);
	return (error);
}
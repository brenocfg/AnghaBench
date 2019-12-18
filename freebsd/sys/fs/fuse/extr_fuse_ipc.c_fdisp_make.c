#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ucred {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
struct mount {int dummy; } ;
struct fuse_dispatcher {int dummy; } ;
struct fuse_data {int dummy; } ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECTIFY_TDCR (struct thread*,struct ucred*) ; 
 void fdisp_make_pid (struct fuse_dispatcher*,int,struct fuse_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*) ; 
 struct fuse_data* fuse_get_mpdata (struct mount*) ; 

void
fdisp_make(struct fuse_dispatcher *fdip, enum fuse_opcode op, struct mount *mp,
    uint64_t nid, struct thread *td, struct ucred *cred)
{
	struct fuse_data *data = fuse_get_mpdata(mp);
	RECTIFY_TDCR(td, cred);

	return fdisp_make_pid(fdip, op, data, nid, td->td_proc->p_pid, cred);
}
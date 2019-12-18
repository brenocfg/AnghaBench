#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_pd {int dummy; } ;
struct ibv_mr {size_t length; void* addr; struct ibv_pd* pd; TYPE_2__* context; } ;
struct TYPE_3__ {int (* rereg_mr ) (struct ibv_mr*,int,struct ibv_pd*,void*,size_t,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int IBV_REREG_MR_CHANGE_ACCESS ; 
 int IBV_REREG_MR_CHANGE_PD ; 
 int IBV_REREG_MR_CHANGE_TRANSLATION ; 
 int IBV_REREG_MR_ERR_CMD ; 
 int IBV_REREG_MR_ERR_CMD_AND_DO_FORK_NEW ; 
 int IBV_REREG_MR_ERR_DONT_FORK_NEW ; 
 int IBV_REREG_MR_ERR_DO_FORK_OLD ; 
 int IBV_REREG_MR_ERR_INPUT ; 
 int IBV_REREG_MR_FLAGS_SUPPORTED ; 
 int /*<<< orphan*/  errno ; 
 int ibv_dofork_range (void*,size_t) ; 
 int ibv_dontfork_range (void*,size_t) ; 
 int stub1 (struct ibv_mr*,int,struct ibv_pd*,void*,size_t,int) ; 

int __ibv_rereg_mr(struct ibv_mr *mr, int flags,
		   struct ibv_pd *pd, void *addr,
		   size_t length, int access)
{
	int dofork_onfail = 0;
	int err;
	void *old_addr;
	size_t old_len;

	if (flags & ~IBV_REREG_MR_FLAGS_SUPPORTED) {
		errno = EINVAL;
		return IBV_REREG_MR_ERR_INPUT;
	}

	if ((flags & IBV_REREG_MR_CHANGE_TRANSLATION) &&
	    (!length || !addr)) {
		errno = EINVAL;
		return IBV_REREG_MR_ERR_INPUT;
	}

	if (access && !(flags & IBV_REREG_MR_CHANGE_ACCESS)) {
		errno = EINVAL;
		return IBV_REREG_MR_ERR_INPUT;
	}

	if (!mr->context->ops.rereg_mr) {
		errno = ENOSYS;
		return IBV_REREG_MR_ERR_INPUT;
	}

	if (flags & IBV_REREG_MR_CHANGE_TRANSLATION) {
		err = ibv_dontfork_range(addr, length);
		if (err)
			return IBV_REREG_MR_ERR_DONT_FORK_NEW;
		dofork_onfail = 1;
	}

	old_addr = mr->addr;
	old_len = mr->length;
	err = mr->context->ops.rereg_mr(mr, flags, pd, addr, length, access);
	if (!err) {
		if (flags & IBV_REREG_MR_CHANGE_PD)
			mr->pd = pd;
		if (flags & IBV_REREG_MR_CHANGE_TRANSLATION) {
			mr->addr    = addr;
			mr->length  = length;
			err = ibv_dofork_range(old_addr, old_len);
			if (err)
				return IBV_REREG_MR_ERR_DO_FORK_OLD;
		}
	} else {
		err = IBV_REREG_MR_ERR_CMD;
		if (dofork_onfail) {
			if (ibv_dofork_range(addr, length))
				err = IBV_REREG_MR_ERR_CMD_AND_DO_FORK_NEW;
		}
	}

	return err;
}
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
struct ibv_rereg_mr_resp {int dummy; } ;
struct ibv_rereg_mr {int dummy; } ;
struct ibv_pd {int dummy; } ;
struct ibv_mr {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ENOTSUP ; 
 int IBV_REREG_MR_KEEP_VALID ; 
 int ibv_cmd_rereg_mr (struct ibv_mr*,int,void*,size_t,uintptr_t,int,struct ibv_pd*,struct ibv_rereg_mr*,int,struct ibv_rereg_mr_resp*,int) ; 

int mlx4_rereg_mr(struct ibv_mr *mr,
		  int flags,
		  struct ibv_pd *pd, void *addr,
		  size_t length, int access)
{
	struct ibv_rereg_mr cmd;
	struct ibv_rereg_mr_resp resp;

	if (flags & IBV_REREG_MR_KEEP_VALID)
		return ENOTSUP;

	return ibv_cmd_rereg_mr(mr, flags, addr, length,
				(uintptr_t)addr,
				access, pd,
				&cmd, sizeof(cmd),
				&resp, sizeof(resp));
}
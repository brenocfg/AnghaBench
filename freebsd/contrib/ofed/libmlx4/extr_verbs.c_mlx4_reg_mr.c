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
struct ibv_reg_mr_resp {int dummy; } ;
struct ibv_reg_mr {int dummy; } ;
struct ibv_pd {int dummy; } ;
struct ibv_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_mr*) ; 
 int ibv_cmd_reg_mr (struct ibv_pd*,void*,size_t,uintptr_t,int,struct ibv_mr*,struct ibv_reg_mr*,int,struct ibv_reg_mr_resp*,int) ; 
 struct ibv_mr* malloc (int) ; 

struct ibv_mr *mlx4_reg_mr(struct ibv_pd *pd, void *addr, size_t length,
			   int access)
{
	struct ibv_mr *mr;
	struct ibv_reg_mr cmd;
	struct ibv_reg_mr_resp resp;
	int ret;

	mr = malloc(sizeof *mr);
	if (!mr)
		return NULL;

	ret = ibv_cmd_reg_mr(pd, addr, length, (uintptr_t) addr,
			     access, mr, &cmd, sizeof cmd,
			     &resp, sizeof resp);
	if (ret) {
		free(mr);
		return NULL;
	}

	return mr;
}
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
struct ibv_pd {TYPE_2__* context; } ;
struct ibv_mr {size_t length; void* addr; struct ibv_pd* pd; TYPE_2__* context; } ;
struct TYPE_3__ {struct ibv_mr* (* reg_mr ) (struct ibv_pd*,void*,size_t,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_dofork_range (void*,size_t) ; 
 scalar_t__ ibv_dontfork_range (void*,size_t) ; 
 struct ibv_mr* stub1 (struct ibv_pd*,void*,size_t,int) ; 

struct ibv_mr *__ibv_reg_mr(struct ibv_pd *pd, void *addr,
			    size_t length, int access)
{
	struct ibv_mr *mr;

	if (ibv_dontfork_range(addr, length))
		return NULL;

	mr = pd->context->ops.reg_mr(pd, addr, length, access);
	if (mr) {
		mr->context = pd->context;
		mr->pd      = pd;
		mr->addr    = addr;
		mr->length  = length;
	} else
		ibv_dofork_range(addr, length);

	return mr;
}
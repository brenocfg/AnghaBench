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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int dummy; } ;
struct rw_mem_args {int /*<<< orphan*/  val; int /*<<< orphan*/  size; int /*<<< orphan*/  operation; } ;
struct mem_range {int (* handler ) (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; } ;

/* Variables and functions */
 int stub1 (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rw_mem_cb(struct vmctx *ctx, int vcpu, uint64_t paddr, struct mem_range *mr,
    void *arg)
{
	struct rw_mem_args *rma;

	rma = arg;
	return (mr->handler(ctx, vcpu, rma->operation, paddr, rma->size,
	    rma->val, mr->arg1, mr->arg2));
}
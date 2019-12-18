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
struct rw_mem_args {int size; int /*<<< orphan*/  operation; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_F_WRITE ; 
 int access_memory (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rw_mem_args*) ; 
 int /*<<< orphan*/  rw_mem_cb ; 

int
write_mem(struct vmctx *ctx, int vcpu, uint64_t gpa, uint64_t wval, int size)
{
	struct rw_mem_args rma;

	rma.val = &wval;
	rma.size = size;
	rma.operation = MEM_F_WRITE;
	return (access_memory(ctx, vcpu, gpa, rw_mem_cb, &rma));
}
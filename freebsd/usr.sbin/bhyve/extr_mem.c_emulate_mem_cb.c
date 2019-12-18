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
struct mem_range {int dummy; } ;
struct emulate_mem_args {int /*<<< orphan*/  paging; int /*<<< orphan*/  vie; } ;

/* Variables and functions */
 int /*<<< orphan*/  mem_read ; 
 int /*<<< orphan*/  mem_write ; 
 int vmm_emulate_instruction (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_range*) ; 

__attribute__((used)) static int
emulate_mem_cb(struct vmctx *ctx, int vcpu, uint64_t paddr, struct mem_range *mr,
    void *arg)
{
	struct emulate_mem_args *ema;

	ema = arg;
	return (vmm_emulate_instruction(ctx, vcpu, paddr, ema->vie, ema->paging,
	    mem_read, mem_write, mr));
}
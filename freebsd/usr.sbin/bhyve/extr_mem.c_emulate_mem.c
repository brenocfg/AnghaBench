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
struct vm_guest_paging {int dummy; } ;
struct vie {int dummy; } ;
struct emulate_mem_args {struct vm_guest_paging* paging; struct vie* vie; } ;

/* Variables and functions */
 int access_memory (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct emulate_mem_args*) ; 
 int /*<<< orphan*/  emulate_mem_cb ; 

int
emulate_mem(struct vmctx *ctx, int vcpu, uint64_t paddr, struct vie *vie,
    struct vm_guest_paging *paging)

{
	struct emulate_mem_args ema;

	ema.vie = vie;
	ema.paging = paging;
	return (access_memory(ctx, vcpu, paddr, emulate_mem_cb, &ema));
}
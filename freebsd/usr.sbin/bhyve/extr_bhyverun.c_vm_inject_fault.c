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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int vm_inject_exception (struct vmctx*,int,int,int,int,int) ; 

void
vm_inject_fault(void *arg, int vcpu, int vector, int errcode_valid,
    int errcode)
{
	struct vmctx *ctx;
	int error, restart_instruction;

	ctx = arg;
	restart_instruction = 1;

	error = vm_inject_exception(ctx, vcpu, vector, errcode_valid, errcode,
	    restart_instruction);
	assert(error == 0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int tf_spsr; int tf_r0; int tf_r1; int tf_r2; int tf_r3; int tf_r4; int tf_r5; int tf_r6; int tf_r7; int tf_r8; int tf_r9; int tf_r10; int tf_r11; int tf_r12; int tf_usr_sp; int tf_usr_lr; int tf_pc; } ;
struct thread {struct trapframe* td_frame; } ;
struct TYPE_3__ {int* __gregs; int /*<<< orphan*/  mc_spare; int /*<<< orphan*/ * mc_vfp_ptr; scalar_t__ mc_vfp_size; } ;
typedef  TYPE_1__ mcontext_t ;
typedef  int __greg_t ;

/* Variables and functions */
 int GET_MC_CLEAR_RET ; 
 int PSR_C ; 
 size_t _REG_CPSR ; 
 size_t _REG_LR ; 
 size_t _REG_PC ; 
 size_t _REG_R0 ; 
 size_t _REG_R1 ; 
 size_t _REG_R10 ; 
 size_t _REG_R11 ; 
 size_t _REG_R12 ; 
 size_t _REG_R2 ; 
 size_t _REG_R3 ; 
 size_t _REG_R4 ; 
 size_t _REG_R5 ; 
 size_t _REG_R6 ; 
 size_t _REG_R7 ; 
 size_t _REG_R8 ; 
 size_t _REG_R9 ; 
 size_t _REG_SP ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
get_mcontext(struct thread *td, mcontext_t *mcp, int clear_ret)
{
	struct trapframe *tf = td->td_frame;
	__greg_t *gr = mcp->__gregs;

	if (clear_ret & GET_MC_CLEAR_RET) {
		gr[_REG_R0] = 0;
		gr[_REG_CPSR] = tf->tf_spsr & ~PSR_C;
	} else {
		gr[_REG_R0]   = tf->tf_r0;
		gr[_REG_CPSR] = tf->tf_spsr;
	}
	gr[_REG_R1]   = tf->tf_r1;
	gr[_REG_R2]   = tf->tf_r2;
	gr[_REG_R3]   = tf->tf_r3;
	gr[_REG_R4]   = tf->tf_r4;
	gr[_REG_R5]   = tf->tf_r5;
	gr[_REG_R6]   = tf->tf_r6;
	gr[_REG_R7]   = tf->tf_r7;
	gr[_REG_R8]   = tf->tf_r8;
	gr[_REG_R9]   = tf->tf_r9;
	gr[_REG_R10]  = tf->tf_r10;
	gr[_REG_R11]  = tf->tf_r11;
	gr[_REG_R12]  = tf->tf_r12;
	gr[_REG_SP]   = tf->tf_usr_sp;
	gr[_REG_LR]   = tf->tf_usr_lr;
	gr[_REG_PC]   = tf->tf_pc;

	mcp->mc_vfp_size = 0;
	mcp->mc_vfp_ptr = NULL;
	memset(&mcp->mc_spare, 0, sizeof(mcp->mc_spare));

	return (0);
}
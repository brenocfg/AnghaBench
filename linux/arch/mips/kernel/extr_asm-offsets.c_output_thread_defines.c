#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  trap_nr; int /*<<< orphan*/  error_code; int /*<<< orphan*/  cp0_baduaddr; int /*<<< orphan*/  cp0_badvaddr; int /*<<< orphan*/  cp0_status; int /*<<< orphan*/  reg31; int /*<<< orphan*/  reg30; int /*<<< orphan*/  reg29; int /*<<< orphan*/  reg23; int /*<<< orphan*/  reg22; int /*<<< orphan*/  reg21; int /*<<< orphan*/  reg20; int /*<<< orphan*/  reg19; int /*<<< orphan*/  reg18; int /*<<< orphan*/  reg17; int /*<<< orphan*/  reg16; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_BUADDR ; 
 int /*<<< orphan*/  THREAD_BVADDR ; 
 int /*<<< orphan*/  THREAD_ECODE ; 
 int /*<<< orphan*/  THREAD_REG16 ; 
 int /*<<< orphan*/  THREAD_REG17 ; 
 int /*<<< orphan*/  THREAD_REG18 ; 
 int /*<<< orphan*/  THREAD_REG19 ; 
 int /*<<< orphan*/  THREAD_REG20 ; 
 int /*<<< orphan*/  THREAD_REG21 ; 
 int /*<<< orphan*/  THREAD_REG22 ; 
 int /*<<< orphan*/  THREAD_REG23 ; 
 int /*<<< orphan*/  THREAD_REG29 ; 
 int /*<<< orphan*/  THREAD_REG30 ; 
 int /*<<< orphan*/  THREAD_REG31 ; 
 int /*<<< orphan*/  THREAD_STATUS ; 
 int /*<<< orphan*/  THREAD_TRAPNO ; 
 int /*<<< orphan*/  task_struct ; 
 TYPE_1__ thread ; 

void output_thread_defines(void)
{
	COMMENT("MIPS specific thread_struct offsets.");
	OFFSET(THREAD_REG16, task_struct, thread.reg16);
	OFFSET(THREAD_REG17, task_struct, thread.reg17);
	OFFSET(THREAD_REG18, task_struct, thread.reg18);
	OFFSET(THREAD_REG19, task_struct, thread.reg19);
	OFFSET(THREAD_REG20, task_struct, thread.reg20);
	OFFSET(THREAD_REG21, task_struct, thread.reg21);
	OFFSET(THREAD_REG22, task_struct, thread.reg22);
	OFFSET(THREAD_REG23, task_struct, thread.reg23);
	OFFSET(THREAD_REG29, task_struct, thread.reg29);
	OFFSET(THREAD_REG30, task_struct, thread.reg30);
	OFFSET(THREAD_REG31, task_struct, thread.reg31);
	OFFSET(THREAD_STATUS, task_struct,
	       thread.cp0_status);

	OFFSET(THREAD_BVADDR, task_struct, \
	       thread.cp0_badvaddr);
	OFFSET(THREAD_BUADDR, task_struct, \
	       thread.cp0_baduaddr);
	OFFSET(THREAD_ECODE, task_struct, \
	       thread.error_code);
	OFFSET(THREAD_TRAPNO, task_struct, thread.trap_nr);
	BLANK();
}
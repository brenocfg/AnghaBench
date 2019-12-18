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

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_STACK_SIZE ; 
 int /*<<< orphan*/  IRQ_STACK_START ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_MASK ; 
 int /*<<< orphan*/  THREAD_SIZE ; 
 int /*<<< orphan*/  TI_ADDR_LIMIT ; 
 int /*<<< orphan*/  TI_CPU ; 
 int /*<<< orphan*/  TI_FLAGS ; 
 int /*<<< orphan*/  TI_PRE_COUNT ; 
 int /*<<< orphan*/  TI_REGS ; 
 int /*<<< orphan*/  TI_TASK ; 
 int /*<<< orphan*/  TI_TP_VALUE ; 
 int /*<<< orphan*/  _IRQ_STACK_SIZE ; 
 int /*<<< orphan*/  _IRQ_STACK_START ; 
 int /*<<< orphan*/  _THREAD_MASK ; 
 int /*<<< orphan*/  _THREAD_SIZE ; 
 int /*<<< orphan*/  addr_limit ; 
 int /*<<< orphan*/  cpu ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  preempt_count ; 
 int /*<<< orphan*/  regs ; 
 int /*<<< orphan*/  task ; 
 int /*<<< orphan*/  thread_info ; 
 int /*<<< orphan*/  tp_value ; 

void output_thread_info_defines(void)
{
	COMMENT("MIPS thread_info offsets.");
	OFFSET(TI_TASK, thread_info, task);
	OFFSET(TI_FLAGS, thread_info, flags);
	OFFSET(TI_TP_VALUE, thread_info, tp_value);
	OFFSET(TI_CPU, thread_info, cpu);
	OFFSET(TI_PRE_COUNT, thread_info, preempt_count);
	OFFSET(TI_ADDR_LIMIT, thread_info, addr_limit);
	OFFSET(TI_REGS, thread_info, regs);
	DEFINE(_THREAD_SIZE, THREAD_SIZE);
	DEFINE(_THREAD_MASK, THREAD_MASK);
	DEFINE(_IRQ_STACK_SIZE, IRQ_STACK_SIZE);
	DEFINE(_IRQ_STACK_START, IRQ_STACK_START);
	BLANK();
}
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
struct trapframe {int dummy; } ;
struct stack {int dummy; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_save (struct stack*) ; 
 int /*<<< orphan*/  stack_sbuf_print_ddb (int /*<<< orphan*/ ,struct stack*) ; 
 int /*<<< orphan*/  stack_zero (struct stack*) ; 
 int /*<<< orphan*/  vcpu_id ; 
 int /*<<< orphan*/  xc_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xendebug_filter(void *arg)
{
#if defined(STACK) && defined(DDB)
	struct stack st;
	struct trapframe *frame;

	frame = arg;
	stack_zero(&st);
	stack_save(&st);

	mtx_lock_spin(&lock);
	sbuf_clear(buf);
	xc_printf("Printing stack trace vCPU%d\n", PCPU_GET(vcpu_id));
	stack_sbuf_print_ddb(buf, &st);
	sbuf_finish(buf);
	mtx_unlock_spin(&lock);
#endif

	return (FILTER_HANDLED);
}
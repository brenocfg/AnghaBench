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
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_ptrace_hw_breakpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tagged_addr_state () ; 
 int /*<<< orphan*/  fpsimd_flush_thread () ; 
 int /*<<< orphan*/  tls_thread_flush () ; 

void flush_thread(void)
{
	fpsimd_flush_thread();
	tls_thread_flush();
	flush_ptrace_hw_breakpoint(current);
	flush_tagged_addr_state();
}
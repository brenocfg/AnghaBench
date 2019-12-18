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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int trace_cont (int /*<<< orphan*/ ) ; 
 int trace_sc (int /*<<< orphan*/ ) ; 
 scalar_t__ trace_syscalls ; 

__attribute__((used)) static int
trace(pid_t pid)
{

	return (trace_syscalls ? trace_sc(pid) : trace_cont(pid));
}
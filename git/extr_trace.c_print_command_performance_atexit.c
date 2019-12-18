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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 TYPE_1__ command_line ; 
 int /*<<< orphan*/  trace_performance_leave (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_command_performance_atexit(void)
{
	trace_performance_leave("git command:%s", command_line.buf);
}
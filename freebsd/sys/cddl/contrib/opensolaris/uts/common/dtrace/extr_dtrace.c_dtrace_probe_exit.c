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
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_2__ {scalar_t__ t_dtrace_inprobe; } ;

/* Variables and functions */
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_probe_exit(dtrace_icookie_t cookie)
{

	curthread->t_dtrace_inprobe = 0;
	dtrace_interrupt_enable(cookie);
}
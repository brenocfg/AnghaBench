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
struct TYPE_3__ {int ss_flags; } ;
typedef  TYPE_1__ stack_t ;

/* Variables and functions */
 int SS_ONSTACK ; 
 int /*<<< orphan*/  sigaltstack (int /*<<< orphan*/ *,TYPE_1__*) ; 

int os_is_signal_stack(void)
{
	stack_t ss;
	sigaltstack(NULL, &ss);

	return ss.ss_flags & SS_ONSTACK;
}
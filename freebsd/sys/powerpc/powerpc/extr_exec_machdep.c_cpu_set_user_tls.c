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
struct thread {TYPE_1__* td_frame; int /*<<< orphan*/  td_proc; } ;
typedef  void* register_t ;
struct TYPE_2__ {void** fixreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_LP64 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cpu_set_user_tls(struct thread *td, void *tls_base)
{

	if (SV_PROC_FLAG(td->td_proc, SV_LP64))
		td->td_frame->fixreg[13] = (register_t)tls_base + 0x7010;
	else
		td->td_frame->fixreg[2] = (register_t)tls_base + 0x7008;
	return (0);
}
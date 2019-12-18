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
struct TYPE_2__ {int /*<<< orphan*/  uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct faultinfo {int dummy; } ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FAULTINFO_FROM_MC (struct faultinfo,int /*<<< orphan*/ *) ; 
 scalar_t__ STUB_DATA ; 
 int /*<<< orphan*/  trap_myself () ; 

void __attribute__ ((__section__ (".__syscall_stub")))
stub_segv_handler(int sig, siginfo_t *info, void *p)
{
	ucontext_t *uc = p;

	GET_FAULTINFO_FROM_MC(*((struct faultinfo *) STUB_DATA),
			      &uc->uc_mcontext);
	trap_myself();
}
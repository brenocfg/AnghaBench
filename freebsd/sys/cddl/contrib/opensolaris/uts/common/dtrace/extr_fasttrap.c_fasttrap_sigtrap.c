#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kthread_t ;
struct TYPE_4__ {scalar_t__ ksi_addr; int /*<<< orphan*/  ksi_code; int /*<<< orphan*/  ksi_signo; } ;
typedef  TYPE_1__ ksiginfo_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAP_DTRACE ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_1__*) ; 
 int /*<<< orphan*/  tdsendsignal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
fasttrap_sigtrap(proc_t *p, kthread_t *t, uintptr_t pc)
{
	ksiginfo_t ksi;

	ksiginfo_init(&ksi);
	ksi.ksi_signo = SIGTRAP;
	ksi.ksi_code = TRAP_DTRACE;
	ksi.ksi_addr = (caddr_t)pc;
	PROC_LOCK(p);
	(void)tdsendsignal(p, t, SIGTRAP, &ksi);
	PROC_UNLOCK(p);
}
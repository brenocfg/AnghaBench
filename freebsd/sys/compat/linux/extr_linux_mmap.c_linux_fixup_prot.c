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
struct thread {int /*<<< orphan*/  td_proc; } ;
struct linux_pemuldata {int persona; } ;

/* Variables and functions */
 int LINUX_READ_IMPLIES_EXEC ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct linux_pemuldata* pem_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
linux_fixup_prot(struct thread *td, int *prot)
{
	struct linux_pemuldata *pem;

	if (SV_PROC_FLAG(td->td_proc, SV_ILP32) && *prot & PROT_READ) {
		pem = pem_find(td->td_proc);
		if (pem->persona & LINUX_READ_IMPLIES_EXEC)
			*prot |= PROT_EXEC;
	}

}
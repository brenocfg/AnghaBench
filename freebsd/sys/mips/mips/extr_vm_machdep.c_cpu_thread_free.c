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
struct TYPE_2__ {int /*<<< orphan*/ * md_ucop2; int /*<<< orphan*/ * md_cop2; } ;
struct thread {TYPE_1__ td_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  octeon_cop2_free_ctx (int /*<<< orphan*/ *) ; 

void
cpu_thread_free(struct thread *td)
{
#ifdef  CPU_CNMIPS
	if (td->td_md.md_cop2)
		octeon_cop2_free_ctx(td->td_md.md_cop2);
	if (td->td_md.md_ucop2)
		octeon_cop2_free_ctx(td->td_md.md_ucop2);
	td->td_md.md_cop2 = NULL;
	td->td_md.md_ucop2 = NULL;
#endif
}
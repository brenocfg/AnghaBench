#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dtpr_name; int /*<<< orphan*/  dtpr_func; int /*<<< orphan*/  dtpr_mod; TYPE_1__* dtpr_provider; } ;
typedef  TYPE_2__ dtrace_probe_t ;
struct TYPE_7__ {TYPE_2__* dte_probe; } ;
typedef  TYPE_3__ dtrace_ecb_t ;
struct TYPE_5__ {int /*<<< orphan*/  dtpv_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/ * dtrace_casptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_destructive_disallow ; 
 int /*<<< orphan*/  dtrace_panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * dtrace_panicked ; 

__attribute__((used)) static void
dtrace_action_panic(dtrace_ecb_t *ecb)
{
	dtrace_probe_t *probe = ecb->dte_probe;

	/*
	 * It's impossible to be taking action on the NULL probe.
	 */
	ASSERT(probe != NULL);

	if (dtrace_destructive_disallow)
		return;

	if (dtrace_panicked != NULL)
		return;

	if (dtrace_casptr(&dtrace_panicked, NULL, curthread) != NULL)
		return;

	/*
	 * We won the right to panic.  (We want to be sure that only one
	 * thread calls panic() from dtrace_probe(), and that panic() is
	 * called exactly once.)
	 */
	dtrace_panic("dtrace: panic action at probe %s:%s:%s:%s (ecb %p)",
	    probe->dtpr_provider->dtpv_name, probe->dtpr_mod,
	    probe->dtpr_func, probe->dtpr_name, (void *)ecb);
}
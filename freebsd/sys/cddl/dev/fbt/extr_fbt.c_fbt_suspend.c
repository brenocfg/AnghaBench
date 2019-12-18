#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nenabled; scalar_t__ loadcnt; } ;
typedef  TYPE_1__ modctl_t ;
struct TYPE_5__ {scalar_t__ fbtp_loadcnt; int /*<<< orphan*/  fbtp_savedval; struct TYPE_5__* fbtp_probenext; TYPE_1__* fbtp_ctl; } ;
typedef  TYPE_2__ fbt_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  fbt_patch_tracepoint (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fbt_suspend(void *arg, dtrace_id_t id, void *parg)
{
	fbt_probe_t *fbt = parg;
	modctl_t *ctl = fbt->fbtp_ctl;

	ASSERT(ctl->nenabled > 0);

	if ((ctl->loadcnt != fbt->fbtp_loadcnt))
		return;

	for (; fbt != NULL; fbt = fbt->fbtp_probenext)
		fbt_patch_tracepoint(fbt, fbt->fbtp_savedval);
}
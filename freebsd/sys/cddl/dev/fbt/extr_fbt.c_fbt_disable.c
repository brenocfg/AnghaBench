#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nenabled; scalar_t__ loadcnt; } ;
typedef  TYPE_1__ modctl_t ;
struct TYPE_6__ {scalar_t__ fbtp_loadcnt; scalar_t__ fbtp_enabled; scalar_t__ fbtp_patchpoint; int /*<<< orphan*/  fbtp_savedval; struct TYPE_6__* fbtp_tracenext; struct TYPE_6__* fbtp_hashnext; struct TYPE_6__* fbtp_probenext; TYPE_1__* fbtp_ctl; } ;
typedef  TYPE_2__ fbt_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t FBT_ADDR2NDX (scalar_t__) ; 
 int /*<<< orphan*/  fbt_patch_tracepoint (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__** fbt_probetab ; 

__attribute__((used)) static void
fbt_disable(void *arg, dtrace_id_t id, void *parg)
{
	fbt_probe_t *fbt = parg, *hash;
	modctl_t *ctl = fbt->fbtp_ctl;

	ASSERT(ctl->nenabled > 0);
	ctl->nenabled--;

	if ((ctl->loadcnt != fbt->fbtp_loadcnt))
		return;

	for (; fbt != NULL; fbt = fbt->fbtp_probenext) {
		fbt->fbtp_enabled--;

		for (hash = fbt_probetab[FBT_ADDR2NDX(fbt->fbtp_patchpoint)];
		    hash != NULL; hash = hash->fbtp_hashnext) {
			if (hash->fbtp_patchpoint == fbt->fbtp_patchpoint) {
				for (; hash != NULL; hash = hash->fbtp_tracenext)
					if (hash->fbtp_enabled > 0)
						break;
				break;
			}
		}
		if (hash == NULL)
			fbt_patch_tracepoint(fbt, fbt->fbtp_savedval);
	}
}
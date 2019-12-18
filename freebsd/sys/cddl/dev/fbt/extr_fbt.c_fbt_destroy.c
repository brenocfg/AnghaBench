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
struct TYPE_4__ {int /*<<< orphan*/  fbt_nentries; } ;
typedef  TYPE_1__ modctl_t ;
struct TYPE_5__ {struct TYPE_5__* fbtp_probenext; TYPE_1__* fbtp_ctl; } ;
typedef  TYPE_2__ fbt_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  fbt_destroy_one (TYPE_2__*) ; 

__attribute__((used)) static void
fbt_destroy(void *arg, dtrace_id_t id, void *parg)
{
	fbt_probe_t *fbt = parg, *next;
	modctl_t *ctl;

	do {
		ctl = fbt->fbtp_ctl;
		ctl->fbt_nentries--;

		next = fbt->fbtp_probenext;
		fbt_destroy_one(fbt);
		fbt = next;
	} while (fbt != NULL);
}
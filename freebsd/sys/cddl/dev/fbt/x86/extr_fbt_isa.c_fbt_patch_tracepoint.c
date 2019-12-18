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
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_3__ {int /*<<< orphan*/ * fbtp_patchpoint; } ;
typedef  TYPE_1__ fbt_probe_t ;
typedef  int /*<<< orphan*/  fbt_patchval_t ;

/* Variables and functions */
 int disable_wp () ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_wp (int) ; 

void
fbt_patch_tracepoint(fbt_probe_t *fbt, fbt_patchval_t val)
{
	register_t intr;
	bool old_wp;

	intr = intr_disable();
	old_wp = disable_wp();
	*fbt->fbtp_patchpoint = val;
	restore_wp(old_wp);
	intr_restore(intr);
}
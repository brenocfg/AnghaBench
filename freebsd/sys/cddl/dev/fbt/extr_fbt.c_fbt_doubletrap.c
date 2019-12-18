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
struct TYPE_4__ {int /*<<< orphan*/  fbtp_savedval; struct TYPE_4__* fbtp_probenext; } ;
typedef  TYPE_1__ fbt_probe_t ;

/* Variables and functions */
 int /*<<< orphan*/  fbt_patch_tracepoint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__** fbt_probetab ; 
 int fbt_probetab_size ; 

__attribute__((used)) static void
fbt_doubletrap(void)
{
	fbt_probe_t *fbt;
	int i;

	for (i = 0; i < fbt_probetab_size; i++) {
		fbt = fbt_probetab[i];

		for (; fbt != NULL; fbt = fbt->fbtp_probenext)
			fbt_patch_tracepoint(fbt, fbt->fbtp_savedval);
	}
}
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

/* Variables and functions */
 int /*<<< orphan*/  M_FBT ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dtrace_doubletrap_func ; 
 int /*<<< orphan*/  dtrace_invop_remove (int /*<<< orphan*/ ) ; 
 int dtrace_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbt_cdev ; 
 int /*<<< orphan*/  fbt_id ; 
 int /*<<< orphan*/  fbt_invop ; 
 int /*<<< orphan*/ * fbt_probetab ; 
 scalar_t__ fbt_probetab_mask ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fbt_unload()
{
	int error = 0;

	/* De-register the invalid opcode handler. */
	dtrace_invop_remove(fbt_invop);

	dtrace_doubletrap_func = NULL;

	/* De-register this DTrace provider. */
	if ((error = dtrace_unregister(fbt_id)) != 0)
		return (error);

	/* Free the probe table. */
	free(fbt_probetab, M_FBT);
	fbt_probetab = NULL;
	fbt_probetab_mask = 0;

	destroy_dev(fbt_cdev);

	return (error);
}
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
typedef  int /*<<< orphan*/  fbt_probe_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_PRIV_USER ; 
 int FBT_PROBETAB_SIZE ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  M_FBT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  dtrace_doubletrap_func ; 
 int /*<<< orphan*/  dtrace_invop_add (int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fbt_attr ; 
 int /*<<< orphan*/  fbt_cdev ; 
 int /*<<< orphan*/  fbt_cdevsw ; 
 int /*<<< orphan*/  fbt_doubletrap ; 
 int /*<<< orphan*/  fbt_id ; 
 int /*<<< orphan*/  fbt_invop ; 
 int /*<<< orphan*/  fbt_linker_file_cb ; 
 int /*<<< orphan*/  fbt_pops ; 
 int /*<<< orphan*/  fbt_probetab ; 
 int fbt_probetab_mask ; 
 int fbt_probetab_size ; 
 int /*<<< orphan*/  linker_file_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fbt_load(void *dummy)
{
	/* Create the /dev/dtrace/fbt entry. */
	fbt_cdev = make_dev(&fbt_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600,
	    "dtrace/fbt");

	/* Default the probe table size if not specified. */
	if (fbt_probetab_size == 0)
		fbt_probetab_size = FBT_PROBETAB_SIZE;

	/* Choose the hash mask for the probe table. */
	fbt_probetab_mask = fbt_probetab_size - 1;

	/* Allocate memory for the probe table. */
	fbt_probetab =
	    malloc(fbt_probetab_size * sizeof (fbt_probe_t *), M_FBT, M_WAITOK | M_ZERO);

	dtrace_doubletrap_func = fbt_doubletrap;
	dtrace_invop_add(fbt_invop);

	if (dtrace_register("fbt", &fbt_attr, DTRACE_PRIV_USER,
	    NULL, &fbt_pops, NULL, &fbt_id) != 0)
		return;

	/* Create probes for the kernel and already-loaded modules. */
	linker_file_foreach(fbt_linker_file_cb, NULL);
}
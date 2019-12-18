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
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  debugf (char*) ; 
 int fdt_add_subnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fdt_getprop (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdt_platform_fixups () ; 
 int /*<<< orphan*/  fdt_setprop (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_setup_fdtp () ; 
 int fdt_subnode_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fdtp ; 

__attribute__((used)) static int
fdt_fixup(void)
{
	int chosen;

	debugf("fdt_fixup()\n");

	if (fdtp == NULL && fdt_setup_fdtp() != 0)
		return (0);

	/* Create /chosen node (if not exists) */
	if ((chosen = fdt_subnode_offset(fdtp, 0, "chosen")) ==
	    -FDT_ERR_NOTFOUND)
		chosen = fdt_add_subnode(fdtp, 0, "chosen");

	/* Value assigned to fixup-applied does not matter. */
	if (fdt_getprop(fdtp, chosen, "fixup-applied", NULL))
		return (1);

	fdt_platform_fixups();

	/*
	 * Re-fetch the /chosen subnode; our fixups may apply overlays or add
	 * nodes/properties that invalidate the offset we grabbed or created
	 * above, so we can no longer trust it.
	 */
	chosen = fdt_subnode_offset(fdtp, 0, "chosen");
	fdt_setprop(fdtp, chosen, "fixup-applied", NULL, 0);
	return (1);
}
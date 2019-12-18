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
typedef  int /*<<< orphan*/  ofw_t ;
typedef  int cell_t ;

/* Variables and functions */
 int ofw_fdt_fixup (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static int
ofw_fdt_interpret(ofw_t ofw, const char *cmd, int nret, cell_t *retvals)
{
#if defined(FDT_MARVELL)
	int rv;

	/*
	 * Note: FDT does not have the possibility to 'interpret' commands,
	 * but we abuse the interface a bit to use it for doing non-standard
	 * operations on the device tree blob.
	 *
	 * Currently the only supported 'command' is to trigger performing
	 * fixups.
	 */
	if (strncmp("perform-fixup", cmd, 13) != 0)
		return (0);

	rv = ofw_fdt_fixup(ofw);
	if (nret > 0)
		retvals[0] = rv;

	return (rv);
#else
	return (0);
#endif
}
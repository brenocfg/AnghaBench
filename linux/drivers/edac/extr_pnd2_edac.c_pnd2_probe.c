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
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int get_registers () ; 
 int /*<<< orphan*/  pnd2_mci ; 
 int pnd2_register_mci (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pnd2_probe(void)
{
	int rc;

	edac_dbg(2, "\n");
	rc = get_registers();
	if (rc)
		return rc;

	return pnd2_register_mci(&pnd2_mci);
}
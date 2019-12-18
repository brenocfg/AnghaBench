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
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pnd2_mci ; 
 int /*<<< orphan*/  pnd2_unregister_mci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnd2_remove(void)
{
	edac_dbg(0, "\n");
	pnd2_unregister_mci(pnd2_mci);
}
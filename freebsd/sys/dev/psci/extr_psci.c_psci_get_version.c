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
 int PSCI_RETVAL_NOT_SUPPORTED ; 
 int _psci_get_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * psci_softc ; 

int
psci_get_version(void)
{

	if (psci_softc == NULL)
		return (PSCI_RETVAL_NOT_SUPPORTED);
	return (_psci_get_version(psci_softc));
}
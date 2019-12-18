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
typedef  scalar_t__ uint32_t ;
struct psci_softc {scalar_t__* psci_fnids; } ;

/* Variables and functions */
 size_t PSCI_FN_VERSION ; 
 int PSCI_RETVAL_NOT_SUPPORTED ; 
 int psci_call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_psci_get_version(struct psci_softc *sc)
{
	uint32_t fnid;

	/* PSCI version wasn't supported in v0.1. */
	fnid = sc->psci_fnids[PSCI_FN_VERSION];
	if (fnid)
		return (psci_call(fnid, 0, 0, 0));

	return (PSCI_RETVAL_NOT_SUPPORTED);
}
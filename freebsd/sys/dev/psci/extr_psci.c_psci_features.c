#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  psci_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSCI_FNID_FEATURES ; 
 int /*<<< orphan*/  PSCI_RETVAL_NOT_SUPPORTED ; 
 int PSCI_VER_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psci_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* psci_softc ; 

int32_t
psci_features(uint32_t psci_func_id)
{

	if (psci_softc == NULL)
		return (PSCI_RETVAL_NOT_SUPPORTED);

	/* The feature flags were added to PSCI 1.0 */
	if (PSCI_VER_MAJOR(psci_softc->psci_version) < 1)
		return (PSCI_RETVAL_NOT_SUPPORTED);

	return (psci_call(PSCI_FNID_FEATURES, psci_func_id, 0, 0));
}
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
typedef  enum psci_conduit { ____Placeholder_psci_conduit } psci_conduit ;
struct TYPE_2__ {int conduit; } ;

/* Variables and functions */
#define  PSCI_CONDUIT_HVC 129 
#define  PSCI_CONDUIT_SMC 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  __invoke_psci_fn_hvc ; 
 int /*<<< orphan*/  __invoke_psci_fn_smc ; 
 int /*<<< orphan*/  invoke_psci_fn ; 
 TYPE_1__ psci_ops ; 

__attribute__((used)) static void set_conduit(enum psci_conduit conduit)
{
	switch (conduit) {
	case PSCI_CONDUIT_HVC:
		invoke_psci_fn = __invoke_psci_fn_hvc;
		break;
	case PSCI_CONDUIT_SMC:
		invoke_psci_fn = __invoke_psci_fn_smc;
		break;
	default:
		WARN(1, "Unexpected PSCI conduit %d\n", conduit);
	}

	psci_ops.conduit = conduit;
}
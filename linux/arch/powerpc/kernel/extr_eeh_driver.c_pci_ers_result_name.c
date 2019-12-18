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
typedef  enum pci_ers_result { ____Placeholder_pci_ers_result } pci_ers_result ;

/* Variables and functions */
#define  PCI_ERS_RESULT_CAN_RECOVER 133 
#define  PCI_ERS_RESULT_DISCONNECT 132 
#define  PCI_ERS_RESULT_NEED_RESET 131 
#define  PCI_ERS_RESULT_NONE 130 
#define  PCI_ERS_RESULT_NO_AER_DRIVER 129 
#define  PCI_ERS_RESULT_RECOVERED 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static const char *pci_ers_result_name(enum pci_ers_result result)
{
	switch (result) {
	case PCI_ERS_RESULT_NONE:
		return "none";
	case PCI_ERS_RESULT_CAN_RECOVER:
		return "can recover";
	case PCI_ERS_RESULT_NEED_RESET:
		return "need reset";
	case PCI_ERS_RESULT_DISCONNECT:
		return "disconnect";
	case PCI_ERS_RESULT_RECOVERED:
		return "recovered";
	case PCI_ERS_RESULT_NO_AER_DRIVER:
		return "no AER driver";
	default:
		WARN_ONCE(1, "Unknown result type: %d\n", (int)result);
		return "unknown";
	}
}
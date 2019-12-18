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
struct ena_admin_ena_hw_hints {int dummy; } ;
struct TYPE_2__ {scalar_t__ group; int syndrom; } ;
struct ena_admin_aenq_entry {TYPE_1__ aenq_common_desc; int /*<<< orphan*/  inline_data_w4; } ;
struct ena_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_NOTIFICATION ; 
#define  ENA_ADMIN_UPDATE_HINTS 128 
 int /*<<< orphan*/  ENA_WARN (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ena_update_hints (struct ena_adapter*,struct ena_admin_ena_hw_hints*) ; 

__attribute__((used)) static void ena_notification(void *adapter_data,
    struct ena_admin_aenq_entry *aenq_e)
{
	struct ena_adapter *adapter = (struct ena_adapter *)adapter_data;
	struct ena_admin_ena_hw_hints *hints;

	ENA_WARN(aenq_e->aenq_common_desc.group != ENA_ADMIN_NOTIFICATION,
	    "Invalid group(%x) expected %x\n",	aenq_e->aenq_common_desc.group,
	    ENA_ADMIN_NOTIFICATION);

	switch (aenq_e->aenq_common_desc.syndrom) {
	case ENA_ADMIN_UPDATE_HINTS:
		hints =
		    (struct ena_admin_ena_hw_hints *)(&aenq_e->inline_data_w4);
		ena_update_hints(adapter, hints);
		break;
	default:
		device_printf(adapter->pdev,
		    "Invalid aenq notification link state %d\n",
		    aenq_e->aenq_common_desc.syndrom);
	}
}
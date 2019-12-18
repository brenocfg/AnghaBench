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
struct ena_adapter {int /*<<< orphan*/  ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_com_admin_q_comp_intr_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_aenq_intr_handler (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_intr_msix_mgmnt(void *arg)
{
	struct ena_adapter *adapter = (struct ena_adapter *)arg;

	ena_com_admin_q_comp_intr_handler(adapter->ena_dev);
	if (likely(ENA_FLAG_ISSET(ENA_FLAG_DEVICE_RUNNING, adapter)))
		ena_com_aenq_intr_handler(adapter->ena_dev, arg);
}
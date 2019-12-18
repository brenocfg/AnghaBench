#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_8__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_9__ {scalar_t__ status; int port_protocol; int /*<<< orphan*/  semaphore; } ;
typedef  TYPE_2__ ocs_mgmt_get_port_protocol_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RW ; 
#define  OCS_HW_PORT_PROTOCOL_FC 131 
#define  OCS_HW_PORT_PROTOCOL_FCOE 130 
#define  OCS_HW_PORT_PROTOCOL_ISCSI 129 
#define  OCS_HW_PORT_PROTOCOL_OTHER 128 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_SEM_FOREVER ; 
 int /*<<< orphan*/  ocs_get_bus_dev_func (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_hw_get_port_protocol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_mgmt_emit_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ocs_mgmt_get_port_protocol_cb ; 
 int /*<<< orphan*/  ocs_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_port_protocol(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	ocs_mgmt_get_port_protocol_result_t result;
	uint8_t bus;
	uint8_t dev;
	uint8_t func;

	ocs_sem_init(&(result.semaphore), 0, "get_port_protocol");

	ocs_get_bus_dev_func(ocs, &bus, &dev, &func);

	if(ocs_hw_get_port_protocol(&ocs->hw, func, ocs_mgmt_get_port_protocol_cb, &result) == OCS_HW_RTN_SUCCESS) {
		if (ocs_sem_p(&(result.semaphore), OCS_SEM_FOREVER) != 0) {
			/* Undefined failure */
			ocs_log_err(ocs, "ocs_sem_p failed\n");
		}
		if (result.status == 0) {
			switch (result.port_protocol) {
			case OCS_HW_PORT_PROTOCOL_ISCSI:
				ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "port_protocol", "iSCSI");
				break;
			case OCS_HW_PORT_PROTOCOL_FCOE:
				ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "port_protocol", "FCoE");
				break;
			case OCS_HW_PORT_PROTOCOL_FC:
				ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "port_protocol", "FC");
				break;
			case OCS_HW_PORT_PROTOCOL_OTHER:
				ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "port_protocol", "Other");
				break;
			}
		} else {
			ocs_log_test(ocs, "getting port profile status 0x%x\n", result.status);
			ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "port_protocol", "Unknown");
		}
	}
}
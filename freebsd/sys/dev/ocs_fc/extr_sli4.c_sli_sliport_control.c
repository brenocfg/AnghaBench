#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_INIT_PORT_DELAY_US ; 
 int /*<<< orphan*/  SLI4_REG_SLIPORT_CONTROL ; 
 int SLI4_SLIPORT_CONTROL_IP ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_udelay (int /*<<< orphan*/ ) ; 
 int sli_fw_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  sli_reg_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int32_t
sli_sliport_control(sli4_t *sli4, uint32_t endian)
{
	uint32_t iter;
	int32_t rc;

	rc = -1;

	/* Initialize port, endian */
	sli_reg_write(sli4, SLI4_REG_SLIPORT_CONTROL, endian | SLI4_SLIPORT_CONTROL_IP);

	for (iter = 0; iter < 3000; iter ++) {
		ocs_udelay(SLI4_INIT_PORT_DELAY_US);
		if (sli_fw_ready(sli4) == 1) {
			rc = 0;
			break;
		}
	}

	if (rc != 0) {
		ocs_log_crit(sli4->os, "port failed to become ready after initialization\n");
	}

	return rc;
}
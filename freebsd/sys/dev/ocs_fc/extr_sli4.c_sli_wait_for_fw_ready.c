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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int FALSE ; 
 int SLI4_INIT_PORT_DELAY_US ; 
 int TRUE ; 
 int /*<<< orphan*/  ocs_udelay (int) ; 
 int sli_fw_ready (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
sli_wait_for_fw_ready(sli4_t *sli4, uint32_t timeout_ms)
{
	uint32_t	iter = timeout_ms / (SLI4_INIT_PORT_DELAY_US / 1000);
	uint32_t	ready = FALSE;

	do {
		iter--;
		ocs_udelay(SLI4_INIT_PORT_DELAY_US);
		if (sli_fw_ready(sli4) == 1) {
			ready = TRUE;
		}
	} while (!ready && (iter > 0));

	return ready;
}
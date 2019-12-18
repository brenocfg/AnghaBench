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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int FALSE ; 
#define  SLI4_FC_LOCAL_REJECT_ABORT_REQUESTED 129 
#define  SLI4_FC_LOCAL_REJECT_INVALID_RPI 128 
 scalar_t__ SLI4_FC_WCQE_STATUS_LOCAL_REJECT ; 
 int TRUE ; 

__attribute__((used)) static uint8_t ocs_hw_wcqe_abort_needed(uint16_t status, uint8_t ext, uint8_t xb)
{
	/* if exchange not active, nothing to abort */
	if (!xb) {
		return FALSE;
	}
	if (status == SLI4_FC_WCQE_STATUS_LOCAL_REJECT) {
		switch (ext) {
		/* exceptions where abort is not needed */
		case SLI4_FC_LOCAL_REJECT_INVALID_RPI: /* lancer returns this after unreg_rpi */
		case SLI4_FC_LOCAL_REJECT_ABORT_REQUESTED: /* abort already in progress */
			return FALSE;
		default:
			break;
		}
	}
	return TRUE;
}
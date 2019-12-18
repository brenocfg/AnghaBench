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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ccb_scsiio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_mode_sense_subpage (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_mode_sense(struct ccb_scsiio *csio, uint32_t retries,
    void (*cbfcnp)(struct cam_periph *, union ccb *), uint8_t tag_action,
    int dbd, uint8_t pc, uint8_t page, uint8_t *param_buf, uint32_t param_len,
    uint8_t sense_len, uint32_t timeout)
{

	scsi_mode_sense_subpage(csio, retries, cbfcnp, tag_action, dbd,
	    pc, page, 0, param_buf, param_len, 0, sense_len, timeout);
}
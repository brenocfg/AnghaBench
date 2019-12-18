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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct ccb_scsiio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_mode_select_len (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_mode_select(struct ccb_scsiio *csio, u_int32_t retries,
		 void (*cbfcnp)(struct cam_periph *, union ccb *),
		 u_int8_t tag_action, int scsi_page_fmt, int save_pages,
		 u_int8_t *param_buf, u_int32_t param_len, u_int8_t sense_len,
		 u_int32_t timeout)
{
	scsi_mode_select_len(csio, retries, cbfcnp, tag_action,
			     scsi_page_fmt, save_pages, param_buf,
			     param_len, 0, sense_len, timeout);
}
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
struct ses_ctrl_dev_slot {int /*<<< orphan*/  common; } ;
struct TYPE_2__ {unsigned int elm_idx; int /*<<< orphan*/ * cstat; } ;
typedef  TYPE_1__ encioc_elm_status_t ;
typedef  int elm_type_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
#define  ELMTYP_ARRAY_DEV 129 
#define  ELMTYP_DEVICE 128 
 int /*<<< orphan*/  ENCIOC_GETELMSTAT ; 
 int /*<<< orphan*/  ENCIOC_SETELMSTAT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ses_ctrl_common_set_select (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ses_ctrl_dev_slot_set_rqst_fault (struct ses_ctrl_dev_slot*,int) ; 
 int /*<<< orphan*/  ses_ctrl_dev_slot_set_rqst_ident (struct ses_ctrl_dev_slot*,int) ; 
 int /*<<< orphan*/  xo_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_led(int fd, unsigned int idx, elm_type_t type, bool onoff, bool setfault)
{
	int state = onoff ? 1 : 0;
	encioc_elm_status_t o;
	struct ses_ctrl_dev_slot *slot;

	o.elm_idx = idx;
	if (ioctl(fd, ENCIOC_GETELMSTAT, (caddr_t) &o) < 0) {
		close(fd);
		xo_err(EXIT_FAILURE, "ENCIOC_GETELMSTAT");
	}
	slot = (struct ses_ctrl_dev_slot *) &o.cstat[0];
	switch (type) {
	case ELMTYP_DEVICE:
	case ELMTYP_ARRAY_DEV:
		ses_ctrl_common_set_select(&slot->common, 1);
		if (setfault)
			ses_ctrl_dev_slot_set_rqst_fault(slot, state);
		else
			ses_ctrl_dev_slot_set_rqst_ident(slot, state);
		break;
	default:
		return;
	}
	if (ioctl(fd, ENCIOC_SETELMSTAT, (caddr_t) &o) < 0) {
		close(fd);
		xo_err(EXIT_FAILURE, "ENCIOC_SETELMSTAT");
	}
}
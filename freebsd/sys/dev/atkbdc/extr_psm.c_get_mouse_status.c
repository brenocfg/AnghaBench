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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int PSMC_SEND_DEV_DATA ; 
 int PSMC_SEND_DEV_STATUS ; 
 int PSM_ACK ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_aux_buffer (int /*<<< orphan*/ ,int) ; 
 int read_aux_data (int /*<<< orphan*/ ) ; 
 int send_aux_command (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_mouse_status(KBDC kbdc, int *status, int flag, int len)
{
	int cmd;
	int res;
	int i;

	switch (flag) {
	case 0:
	default:
		cmd = PSMC_SEND_DEV_STATUS;
		break;
	case 1:
		cmd = PSMC_SEND_DEV_DATA;
		break;
	}
	empty_aux_buffer(kbdc, 5);
	res = send_aux_command(kbdc, cmd);
	VLOG(2, (LOG_DEBUG, "psm: SEND_AUX_DEV_%s return code:%04x\n",
	    (flag == 1) ? "DATA" : "STATUS", res));
	if (res != PSM_ACK)
		return (0);

	for (i = 0; i < len; ++i) {
		status[i] = read_aux_data(kbdc);
		if (status[i] < 0)
			break;
	}
	if (len >= 3) {
		for (; i < 3; ++i)
			status[i] = 0;
		VLOG(1, (LOG_DEBUG, "psm: %s %02x %02x %02x\n",
		    (flag == 1) ? "data" : "status", status[0], status[1], status[2]));
	}

	return (i);
}
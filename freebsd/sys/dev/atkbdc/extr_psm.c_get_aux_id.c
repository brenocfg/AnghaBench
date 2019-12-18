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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  PSMC_SEND_DEV_ID ; 
 int PSM_ACK ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_aux_buffer (int /*<<< orphan*/ ,int) ; 
 int read_aux_data (int /*<<< orphan*/ ) ; 
 int send_aux_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_aux_id(KBDC kbdc)
{
	int res;
	int id;

	empty_aux_buffer(kbdc, 5);
	res = send_aux_command(kbdc, PSMC_SEND_DEV_ID);
	VLOG(2, (LOG_DEBUG, "psm: SEND_DEV_ID return code:%04x\n", res));
	if (res != PSM_ACK)
		return (-1);

	/* 10ms delay */
	DELAY(10000);

	id = read_aux_data(kbdc);
	VLOG(2, (LOG_DEBUG, "psm: device ID: %04x\n", id));

	return (id);
}
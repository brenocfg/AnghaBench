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
 int /*<<< orphan*/  PSMC_SET_SAMPLING_RATE ; 
 int PSM_ACK ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int send_aux_command_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
set_mouse_sampling_rate(KBDC kbdc, int rate)
{
	int res;

	res = send_aux_command_and_data(kbdc, PSMC_SET_SAMPLING_RATE, rate);
	VLOG(2, (LOG_DEBUG, "psm: SET_SAMPLING_RATE (%d) %04x\n", rate, res));

	return ((res == PSM_ACK) ? rate : -1);
}
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
 int /*<<< orphan*/  PSMC_ENABLE_DEV ; 
 int PSM_ACK ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int send_aux_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_aux_dev(KBDC kbdc)
{
	int res;

	res = send_aux_command(kbdc, PSMC_ENABLE_DEV);
	VLOG(2, (LOG_DEBUG, "psm: ENABLE_DEV return code:%04x\n", res));

	return (res == PSM_ACK);
}
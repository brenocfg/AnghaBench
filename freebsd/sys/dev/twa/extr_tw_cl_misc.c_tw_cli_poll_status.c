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
struct tw_cli_ctlr_context {int /*<<< orphan*/  ctlr_handle; } ;
typedef  scalar_t__ TW_UINT32 ;
typedef  scalar_t__ TW_TIME ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 scalar_t__ TW_CLI_READ_STATUS_REGISTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_OSL_ESUCCESS ; 
 int /*<<< orphan*/  TW_OSL_ETIMEDOUT ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 int /*<<< orphan*/  tw_osl_delay (int) ; 
 scalar_t__ tw_osl_get_local_time () ; 

TW_INT32
tw_cli_poll_status(struct tw_cli_ctlr_context *ctlr, TW_UINT32 status,
	TW_UINT32 timeout)
{
	TW_TIME		end_time;
	TW_UINT32	status_reg;

	tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	end_time = tw_osl_get_local_time() + timeout;
	do {
		status_reg = TW_CLI_READ_STATUS_REGISTER(ctlr->ctlr_handle);
		if ((status_reg & status) == status)
			/* got the required bit(s) */
			return(TW_OSL_ESUCCESS);

		tw_osl_delay(1000);
	} while (tw_osl_get_local_time() <= end_time);

	return(TW_OSL_ETIMEDOUT);
}
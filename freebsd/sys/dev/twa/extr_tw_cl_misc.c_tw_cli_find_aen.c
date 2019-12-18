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
struct tw_cli_ctlr_context {int aen_head; int max_aens_supported; TYPE_1__* aen_queue; scalar_t__ aen_q_wrapped; int /*<<< orphan*/  ctlr_handle; } ;
struct TYPE_2__ {scalar_t__ aen_code; } ;
typedef  int TW_UINT32 ;
typedef  scalar_t__ TW_UINT16 ;
typedef  int TW_INT32 ;

/* Variables and functions */
 int TW_OSL_EGENFAILURE ; 
 int TW_OSL_ESUCCESS ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 

TW_INT32
tw_cli_find_aen(struct tw_cli_ctlr_context *ctlr, TW_UINT16 aen_code)
{
	TW_UINT32	last_index;
	TW_INT32	i;

	tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	if (ctlr->aen_q_wrapped)
		last_index = ctlr->aen_head;
	else
		last_index = 0;

	i = ctlr->aen_head;
	do {
		i = (i + ctlr->max_aens_supported - 1) %
			ctlr->max_aens_supported;
		if (ctlr->aen_queue[i].aen_code == aen_code)
			return(TW_OSL_ESUCCESS);
	} while (i != last_index);

	return(TW_OSL_EGENFAILURE);
}
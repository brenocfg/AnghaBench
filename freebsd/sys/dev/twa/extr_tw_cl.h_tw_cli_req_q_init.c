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
struct tw_cli_ctlr_context {int /*<<< orphan*/ * req_q_head; } ;
typedef  int /*<<< orphan*/  TW_VOID ;
typedef  size_t TW_UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  TW_CLI_Q_INIT (struct tw_cli_ctlr_context*,size_t) ; 
 int /*<<< orphan*/  TW_CL_Q_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline TW_VOID
tw_cli_req_q_init(struct tw_cli_ctlr_context *ctlr, TW_UINT8 q_type)
{
	TW_CL_Q_INIT(&(ctlr->req_q_head[q_type]));
	TW_CLI_Q_INIT(ctlr, q_type);
}
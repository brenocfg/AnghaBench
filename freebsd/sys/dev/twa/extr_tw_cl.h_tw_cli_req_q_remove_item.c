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
struct tw_cli_req_context {int /*<<< orphan*/  link; struct tw_cli_ctlr_context* ctlr; } ;
struct tw_cli_ctlr_context {int /*<<< orphan*/  gen_lock; int /*<<< orphan*/  ctlr_handle; int /*<<< orphan*/ * req_q_head; } ;
typedef  int /*<<< orphan*/  TW_VOID ;
typedef  size_t TW_UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  TW_CLI_Q_REMOVE (struct tw_cli_ctlr_context*,size_t) ; 
 int /*<<< orphan*/  TW_CL_Q_REMOVE_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_osl_free_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_get_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline TW_VOID
tw_cli_req_q_remove_item(struct tw_cli_req_context *req, TW_UINT8 q_type)
{
	struct tw_cli_ctlr_context	*ctlr = req->ctlr;

	tw_osl_get_lock(ctlr->ctlr_handle, ctlr->gen_lock);
	TW_CL_Q_REMOVE_ITEM(&(ctlr->req_q_head[q_type]), &(req->link));
	TW_CLI_Q_REMOVE(ctlr, q_type);
	tw_osl_free_lock(ctlr->ctlr_handle, ctlr->gen_lock);
}
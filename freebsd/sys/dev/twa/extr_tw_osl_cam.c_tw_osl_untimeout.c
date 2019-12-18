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
struct tw_osli_req_context {scalar_t__ deadline; } ;
struct tw_cl_req_handle {struct tw_osli_req_context* osl_req_ctxt; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */

TW_VOID
tw_osl_untimeout(struct tw_cl_req_handle *req_handle)
{
	struct tw_osli_req_context	*req = req_handle->osl_req_ctxt;

	req->deadline = 0;
}
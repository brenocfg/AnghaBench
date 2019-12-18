#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int window_first; int window_last; int /*<<< orphan*/ * p_log; int /*<<< orphan*/  is_sa_mad; int /*<<< orphan*/  mad_sz; int /*<<< orphan*/  sar; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ osmv_rmpp_send_ctx_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  int /*<<< orphan*/  ib_mad_t ;
typedef  scalar_t__ ib_api_status_t ;
typedef  scalar_t__ cl_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (TYPE_1__*) ; 
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IB_ERROR ; 
 scalar_t__ IB_INVALID_PARAMETER ; 
 scalar_t__ IB_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cl_event_construct (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osmv_mad_is_sa (int /*<<< orphan*/ *) ; 
 scalar_t__ osmv_rmpp_sar_init (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ib_api_status_t
osmv_rmpp_send_ctx_init(osmv_rmpp_send_ctx_t * p_ctx, void *p_arbt_mad,
			uint32_t mad_sz, osm_log_t * p_log)
{
	ib_api_status_t st = IB_SUCCESS;
	cl_status_t cl_st;

	CL_ASSERT(p_ctx);
	if (NULL == p_arbt_mad) {
		return IB_INVALID_PARAMETER;
	}

	if (osmv_mad_is_sa((ib_mad_t *) p_arbt_mad)) {
		p_ctx->is_sa_mad = TRUE;
	} else
		p_ctx->is_sa_mad = FALSE;

	p_ctx->mad_sz = mad_sz;

	cl_event_construct(&p_ctx->event);
	cl_st = cl_event_init(&p_ctx->event, FALSE);
	if (cl_st != CL_SUCCESS) {
		return IB_ERROR;
	}

	st = osmv_rmpp_sar_init(&p_ctx->sar, p_arbt_mad, p_ctx->mad_sz,
				p_ctx->is_sa_mad);
	if (st == IB_SUCCESS) {
		p_ctx->window_first = 1;
		p_ctx->window_last = 1;
	}

	p_ctx->p_log = p_log;
	return st;
}
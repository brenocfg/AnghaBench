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
typedef  void* uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  data_sz; void* hdr_sz; void* data_len; void* p_arbt_mad; } ;
typedef  TYPE_1__ osmv_rmpp_sar_t ;
typedef  int /*<<< orphan*/  ib_api_status_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  IB_SA_DATA_SIZE ; 
 void* IB_SA_MAD_HDR_SIZE ; 
 int /*<<< orphan*/  IB_SUCCESS ; 
 int /*<<< orphan*/  MAD_RMPP_DATA_SIZE ; 
 void* MAD_RMPP_HDR_SIZE ; 

ib_api_status_t
osmv_rmpp_sar_init(osmv_rmpp_sar_t * p_sar, void *p_arbt_mad,
		   uint32_t mad_size, boolean_t is_sa_mad)
{
	CL_ASSERT(p_sar);
	p_sar->p_arbt_mad = p_arbt_mad;
	if (is_sa_mad) {
		p_sar->data_len = mad_size - IB_SA_MAD_HDR_SIZE;
		p_sar->hdr_sz = IB_SA_MAD_HDR_SIZE;
		p_sar->data_sz = IB_SA_DATA_SIZE;
	} else {
		p_sar->data_len = mad_size - MAD_RMPP_HDR_SIZE;
		p_sar->hdr_sz = MAD_RMPP_HDR_SIZE;
		p_sar->data_sz = MAD_RMPP_DATA_SIZE;
	}
	return IB_SUCCESS;
}
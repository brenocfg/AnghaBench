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
typedef  int u_int64_t ;
struct hpt_iop_hba {int dummy; } ;

/* Variables and functions */
 int MVIOP_MU_QUEUE_ADDR_HOST_BIT ; 
 int MVIOP_MU_QUEUE_REQUEST_RETURN_CONTEXT ; 
 int hptiop_mv_outbound_read (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  hptiop_request_callback_mv (struct hpt_iop_hba*,int) ; 

__attribute__((used)) static void hptiop_drain_outbound_queue_mv(struct hpt_iop_hba * hba)
{
	u_int64_t req;

	while ((req = hptiop_mv_outbound_read(hba))) {
		if (req & MVIOP_MU_QUEUE_ADDR_HOST_BIT) {
			if (req & MVIOP_MU_QUEUE_REQUEST_RETURN_CONTEXT) {
				hptiop_request_callback_mv(hba, req);
			}
	    	}
	}
}
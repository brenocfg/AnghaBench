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
struct TYPE_2__ {scalar_t__ ccppp_queue_base; scalar_t__ ccppp_num_queues; } ;

/* Variables and functions */
 scalar_t__ CVMX_HELPER_CFG_INVALID_VALUE ; 
 int CVMX_HELPER_CFG_MAX_PKO_PORT ; 
 TYPE_1__* cvmx_cfg_pko_port ; 
 int /*<<< orphan*/  cvmx_helper_cfg_assert (int) ; 

int __cvmx_helper_cfg_pko_max_queue(void)
{
    int i;

    i = CVMX_HELPER_CFG_MAX_PKO_PORT - 1;

    while (i >= 0)
    {
        if (cvmx_cfg_pko_port[i].ccppp_queue_base !=
	    CVMX_HELPER_CFG_INVALID_VALUE)
	{
	    cvmx_helper_cfg_assert(cvmx_cfg_pko_port[i].ccppp_num_queues > 0);
	    return (cvmx_cfg_pko_port[i].ccppp_queue_base +
	        cvmx_cfg_pko_port[i].ccppp_num_queues);
	}
	i --;
    }

    cvmx_helper_cfg_assert(0); /* shouldn't get here */
    
    return 0;
}
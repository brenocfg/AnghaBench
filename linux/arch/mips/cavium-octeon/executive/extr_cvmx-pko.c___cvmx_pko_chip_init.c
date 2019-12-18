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
typedef  int uint64_t ;

/* Variables and functions */
 int CVMX_PKO_MAX_OUTPUT_QUEUES ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_pko_port_map_o68 () ; 
 int /*<<< orphan*/  __cvmx_pko_queue_alloc_o68 () ; 
 int /*<<< orphan*/  cvmx_pko_config_port (int /*<<< orphan*/ ,int,int,int const*) ; 

__attribute__((used)) static void __cvmx_pko_chip_init(void)
{
	int i;

	if (OCTEON_IS_MODEL(OCTEON_CN68XX)) {
		__cvmx_pko_port_map_o68();
		__cvmx_pko_queue_alloc_o68();
		return;
	}

	/*
	 * Initialize queues
	 */
	for (i = 0; i < CVMX_PKO_MAX_OUTPUT_QUEUES; i++) {
		const uint64_t priority = 8;

		cvmx_pko_config_port(CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID, i, 1,
				     &priority);
	}
}
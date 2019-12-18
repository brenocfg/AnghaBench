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
 int cvmx_helper_get_ipd_port (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pko_config_port (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cvmx_pko_get_base_queue_per_core (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pko_get_num_queues (int) ; 
 int* interface_port_count ; 

__attribute__((used)) static int __cvmx_helper_interface_setup_pko(int interface)
{
	/*
	 * Each packet output queue has an associated priority. The
	 * higher the priority, the more often it can send a packet. A
	 * priority of 8 means it can send in all 8 rounds of
	 * contention. We're going to make each queue one less than
	 * the last.  The vector of priorities has been extended to
	 * support CN5xxx CPUs, where up to 16 queues can be
	 * associated to a port.  To keep backward compatibility we
	 * don't change the initial 8 priorities and replicate them in
	 * the second half.  With per-core PKO queues (PKO lockless
	 * operation) all queues have the same priority.
	 */
	uint64_t priorities[16] =
	    { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };

	/*
	 * Setup the IPD/PIP and PKO for the ports discovered
	 * above. Here packet classification, tagging and output
	 * priorities are set.
	 */
	int ipd_port = cvmx_helper_get_ipd_port(interface, 0);
	int num_ports = interface_port_count[interface];
	while (num_ports--) {
		cvmx_pko_config_port(ipd_port,
				     cvmx_pko_get_base_queue_per_core(ipd_port,
								      0),
				     cvmx_pko_get_num_queues(ipd_port),
				     priorities);
		ipd_port++;
	}
	return 0;
}
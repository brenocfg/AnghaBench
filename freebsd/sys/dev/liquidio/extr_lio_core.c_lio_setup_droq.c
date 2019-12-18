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
struct octeon_device {TYPE_1__** droq; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_count; int /*<<< orphan*/  pkts_credit_reg; } ;

/* Variables and functions */
 int lio_create_droq (struct octeon_device*,int,int,int,void*) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,int) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_setup_droq(struct octeon_device *oct, int q_no, int num_descs,
	       int desc_size, void *app_ctx)
{
	int	ret_val = 0;

	lio_dev_dbg(oct, "Creating Droq: %d\n", q_no);
	/* droq creation and local register settings. */
	ret_val = lio_create_droq(oct, q_no, num_descs, desc_size, app_ctx);
	if (ret_val < 0)
		return (ret_val);

	if (ret_val == 1) {
		lio_dev_dbg(oct, "Using default droq %d\n", q_no);
		return (0);
	}

	/*
	 * Send Credit for Octeon Output queues. Credits are always
         * sent after the output queue is enabled.
         */
	lio_write_csr32(oct, oct->droq[q_no]->pkts_credit_reg,
			oct->droq[q_no]->max_count);

	return (ret_val);
}
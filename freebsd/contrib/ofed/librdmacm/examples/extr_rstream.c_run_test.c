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

/* Variables and functions */
 scalar_t__ dst_addr ; 
 int /*<<< orphan*/  end ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iterations ; 
 int recv_xfer (int /*<<< orphan*/ ) ; 
 int send_xfer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_perf () ; 
 int /*<<< orphan*/  start ; 
 int sync_test () ; 
 int transfer_count ; 
 int /*<<< orphan*/  transfer_size ; 

__attribute__((used)) static int run_test(void)
{
	int ret, i, t;

	ret = sync_test();
	if (ret)
		goto out;

	gettimeofday(&start, NULL);
	for (i = 0; i < iterations; i++) {
		for (t = 0; t < transfer_count; t++) {
			ret = dst_addr ? send_xfer(transfer_size) :
					 recv_xfer(transfer_size);
			if (ret)
				goto out;
		}

		for (t = 0; t < transfer_count; t++) {
			ret = dst_addr ? recv_xfer(transfer_size) :
					 send_xfer(transfer_size);
			if (ret)
				goto out;
		}
	}
	gettimeofday(&end, NULL);
	show_perf();
	ret = 0;

out:
	return ret;
}
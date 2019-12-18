#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_wc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* nodes; } ;
struct TYPE_3__ {int /*<<< orphan*/  cq; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int connections ; 
 int ibv_poll_cq (int /*<<< orphan*/ ,int,struct ibv_wc*) ; 
 int message_count ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_2__ test ; 

__attribute__((used)) static int poll_cqs(void)
{
	struct ibv_wc wc[8];
	int done, i, ret;

	for (i = 0; i < connections; i++) {
		if (!test.nodes[i].connected)
			continue;

		for (done = 0; done < message_count; done += ret) {
			ret = ibv_poll_cq(test.nodes[i].cq, 8, wc);
			if (ret < 0) {
				printf("mckey: failed polling CQ: %d\n", ret);
				return ret;
			}
		}
	}
	return 0;
}
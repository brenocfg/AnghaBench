#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* qs; } ;
struct adapter {TYPE_3__ sge; } ;
struct TYPE_4__ {unsigned long offload_pkts; } ;
struct TYPE_5__ {TYPE_1__ rspq; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  t3_os_sleep (int) ; 

__attribute__((used)) static int
await_mgmt_replies(struct adapter *adap, unsigned long init_cnt,
			      unsigned long n)
{
	int attempts = 5;

	while (adap->sge.qs[0].rspq.offload_pkts < init_cnt + n) {
		if (!--attempts)
			return (ETIMEDOUT);
		t3_os_sleep(10);
	}
	return 0;
}
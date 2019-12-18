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
struct nitrox_device {int nr_queues; int /*<<< orphan*/ ** aqmq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nitrox_cmdq_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nitrox_free_aqm_queues(struct nitrox_device *ndev)
{
	int i;

	for (i = 0; i < ndev->nr_queues; i++) {
		nitrox_cmdq_cleanup(ndev->aqmq[i]);
		kzfree(ndev->aqmq[i]);
		ndev->aqmq[i] = NULL;
	}
}
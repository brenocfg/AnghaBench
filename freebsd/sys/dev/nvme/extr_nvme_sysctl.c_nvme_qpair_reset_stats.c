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
struct nvme_qpair {scalar_t__ num_failures; scalar_t__ num_retries; scalar_t__ num_intr_handler_calls; scalar_t__ num_cmds; } ;

/* Variables and functions */

__attribute__((used)) static void
nvme_qpair_reset_stats(struct nvme_qpair *qpair)
{

	qpair->num_cmds = 0;
	qpair->num_intr_handler_calls = 0;
	qpair->num_retries = 0;
	qpair->num_failures = 0;
}
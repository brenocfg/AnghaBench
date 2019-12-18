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
struct sge_iq {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IQS_BUSY ; 
 int /*<<< orphan*/  IQS_IDLE ; 
 scalar_t__ atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_iq_fl (struct sge_iq*,int /*<<< orphan*/ ) ; 

void
t4_intr(void *arg)
{
	struct sge_iq *iq = arg;

	if (atomic_cmpset_int(&iq->state, IQS_IDLE, IQS_BUSY)) {
		service_iq_fl(iq, 0);
		(void) atomic_cmpset_int(&iq->state, IQS_BUSY, IQS_IDLE);
	}
}
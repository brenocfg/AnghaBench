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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */

__attribute__((used)) static int
vmxnet3_tx_queue_intr_enable(if_ctx_t ctx, uint16_t qid)
{
	/* Not using interrupts for TX */
	return (0);
}
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
struct em_rx_queue {int /*<<< orphan*/  irqs; } ;

/* Variables and functions */
 int FILTER_SCHEDULE_THREAD ; 

__attribute__((used)) static int
em_msix_que(void *arg)
{
	struct em_rx_queue *que = arg;

	++que->irqs;

	return (FILTER_SCHEDULE_THREAD);
}
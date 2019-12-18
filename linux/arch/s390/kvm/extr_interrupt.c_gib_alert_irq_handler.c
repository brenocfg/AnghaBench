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
struct airq_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQIO_GAL ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_gib_alert_list () ; 

__attribute__((used)) static void gib_alert_irq_handler(struct airq_struct *airq, bool floating)
{
	inc_irq_stat(IRQIO_GAL);
	process_gib_alert_list();
}
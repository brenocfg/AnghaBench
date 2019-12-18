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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3c_irq_demux_eint (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s3c_irq_demux_eint0_3(struct irq_desc *desc)
{
	s3c_irq_demux_eint(0, 3);
}
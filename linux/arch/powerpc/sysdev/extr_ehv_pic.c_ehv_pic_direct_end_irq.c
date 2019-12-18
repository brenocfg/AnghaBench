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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int MPIC_EOI ; 
 scalar_t__ mpic_percpu_base_vaddr ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

void ehv_pic_direct_end_irq(struct irq_data *d)
{
	out_be32(mpic_percpu_base_vaddr + MPIC_EOI / 4, 0);
}
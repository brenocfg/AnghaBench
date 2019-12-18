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
typedef  int /*<<< orphan*/  u_int ;
struct xive_irq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  M_XIVE ; 
 struct xive_irq* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_init_irq (struct xive_irq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xive_irq *
xive_configure_irq(u_int irq)
{
	struct xive_irq *irqd;

	irqd = malloc(sizeof(struct xive_irq), M_XIVE, M_WAITOK);

	xive_init_irq(irqd, irq);

	return (irqd);
}
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
struct irq {scalar_t__ res; int /*<<< orphan*/  rid; scalar_t__ tag; } ;
struct adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bzero (struct irq*,int) ; 

__attribute__((used)) static int
t4_free_irq(struct adapter *sc, struct irq *irq)
{
	if (irq->tag)
		bus_teardown_intr(sc->dev, irq->res, irq->tag);
	if (irq->res)
		bus_release_resource(sc->dev, SYS_RES_IRQ, irq->rid, irq->res);

	bzero(irq, sizeof(*irq));

	return (0);
}
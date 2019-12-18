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
typedef  int uint32_t ;
struct mv_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  GPIO_DATA_IN ; 
 int /*<<< orphan*/  GPIO_INT_CAUSE ; 
 int /*<<< orphan*/  GPIO_INT_EDGE_MASK ; 
 int /*<<< orphan*/  GPIO_INT_LEV_MASK ; 
 int /*<<< orphan*/  MV_GPIO_LOCK () ; 
 int /*<<< orphan*/  MV_GPIO_UNLOCK () ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_exec_intr_handlers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mv_gpio_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_gpio_intr(device_t dev, void *arg)
{
	uint32_t int_cause, gpio_val;
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	MV_GPIO_LOCK();

	/*
	 * According to documentation, edge sensitive interrupts are asserted
	 * when unmasked GPIO_INT_CAUSE register bits are set.
	 */
	int_cause = mv_gpio_reg_read(dev, GPIO_INT_CAUSE);
	int_cause &= mv_gpio_reg_read(dev, GPIO_INT_EDGE_MASK);

	/*
	 * Level sensitive interrupts are asserted when unmasked GPIO_DATA_IN
	 * register bits are set.
	 */
	gpio_val = mv_gpio_reg_read(dev, GPIO_DATA_IN);
	gpio_val &= mv_gpio_reg_read(dev, GPIO_INT_LEV_MASK);

	mv_gpio_exec_intr_handlers(dev, int_cause | gpio_val, 0);

	MV_GPIO_UNLOCK();

	return (FILTER_HANDLED);
}
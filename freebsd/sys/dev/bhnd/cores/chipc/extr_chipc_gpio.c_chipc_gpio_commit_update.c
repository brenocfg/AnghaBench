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
struct chipc_gpio_update {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  outen; int /*<<< orphan*/  out; int /*<<< orphan*/  timeroutmask; int /*<<< orphan*/  pullup; int /*<<< orphan*/  pulldown; } ;
struct chipc_gpio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_GPIO_LOCK_ASSERT (struct chipc_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIPC_GPIOCTRL ; 
 int /*<<< orphan*/  CHIPC_GPIOOUT ; 
 int /*<<< orphan*/  CHIPC_GPIOOUTEN ; 
 int /*<<< orphan*/  CHIPC_GPIOPD ; 
 int /*<<< orphan*/  CHIPC_GPIOPU ; 
 int /*<<< orphan*/  CHIPC_GPIOTIMEROUTMASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  chipc_gpio_commit_reg (struct chipc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
chipc_gpio_commit_update(struct chipc_gpio_softc *sc,
    struct chipc_gpio_update *update)
{
	CC_GPIO_LOCK_ASSERT(sc, MA_OWNED);

	/* Commit pulldown/pullup before potentially disabling an output pin */
	chipc_gpio_commit_reg(sc, CHIPC_GPIOPD, &update->pulldown);
	chipc_gpio_commit_reg(sc, CHIPC_GPIOPU, &update->pullup);

	/* Commit output settings before potentially enabling an output pin */
	chipc_gpio_commit_reg(sc, CHIPC_GPIOTIMEROUTMASK,
	    &update->timeroutmask);
	chipc_gpio_commit_reg(sc, CHIPC_GPIOOUT, &update->out);

	/* Commit input/output/tristate modes */
	chipc_gpio_commit_reg(sc, CHIPC_GPIOOUTEN, &update->outen);
	chipc_gpio_commit_reg(sc, CHIPC_GPIOCTRL, &update->ctrl);

	return (0);
}
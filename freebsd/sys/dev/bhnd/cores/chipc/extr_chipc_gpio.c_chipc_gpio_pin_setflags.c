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
typedef  int /*<<< orphan*/  upd ;
typedef  int /*<<< orphan*/  uint32_t ;
struct chipc_gpio_update {int dummy; } ;
struct chipc_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_GPIO_LOCK (struct chipc_gpio_softc*) ; 
 int /*<<< orphan*/  CC_GPIO_UNLOCK (struct chipc_gpio_softc*) ; 
 int /*<<< orphan*/  CC_GPIO_VALID_PIN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int chipc_gpio_commit_update (struct chipc_gpio_softc*,struct chipc_gpio_update*) ; 
 int chipc_gpio_pin_update (struct chipc_gpio_softc*,struct chipc_gpio_update*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct chipc_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct chipc_gpio_update*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
chipc_gpio_pin_setflags(device_t dev, uint32_t pin_num, uint32_t flags)
{
	struct chipc_gpio_softc		*sc;
	struct chipc_gpio_update	 upd;
	int				 error;
	
	sc = device_get_softc(dev);

	if (!CC_GPIO_VALID_PIN(pin_num))
		return (EINVAL);

	/* Produce an update descriptor */
	memset(&upd, 0, sizeof(upd));
	if ((error = chipc_gpio_pin_update(sc, &upd, pin_num, flags)))
		return (error);

	/* Commit the update */
	CC_GPIO_LOCK(sc);
	error = chipc_gpio_commit_update(sc, &upd);
	CC_GPIO_UNLOCK(sc);

	return (error);
}
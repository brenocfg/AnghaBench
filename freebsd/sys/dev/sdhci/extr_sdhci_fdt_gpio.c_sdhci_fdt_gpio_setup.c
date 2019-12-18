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
struct sdhci_slot {int dummy; } ;
struct sdhci_fdt_gpio {struct sdhci_slot* slot; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cd_setup (struct sdhci_fdt_gpio*,int /*<<< orphan*/ ) ; 
 struct sdhci_fdt_gpio* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_setup (struct sdhci_fdt_gpio*,int /*<<< orphan*/ ) ; 

struct sdhci_fdt_gpio *
sdhci_fdt_gpio_setup(device_t dev, struct sdhci_slot *slot)
{
	phandle_t node;
	struct sdhci_fdt_gpio *gpio;

	gpio = malloc(sizeof(*gpio), M_DEVBUF, M_ZERO | M_WAITOK);
	gpio->dev  = dev;
	gpio->slot = slot;

	node = ofw_bus_get_node(dev);

	wp_setup(gpio, node);
	cd_setup(gpio, node);

	return (gpio);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* label; int base; int /*<<< orphan*/  get_multiple; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  names; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  owner; struct device* parent; } ;
struct idi_48_gpio {TYPE_1__ chip; int /*<<< orphan*/  ack_lock; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDI48_NGPIO ; 
 scalar_t__ IDI_48_EXTENT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__* base ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 char* dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct idi_48_gpio*) ; 
 struct idi_48_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const,struct idi_48_gpio*) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,scalar_t__,scalar_t__,char const* const) ; 
 int gpiochip_irqchip_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  idi48_names ; 
 int /*<<< orphan*/  idi_48_gpio_direction_input ; 
 int /*<<< orphan*/  idi_48_gpio_get ; 
 int /*<<< orphan*/  idi_48_gpio_get_direction ; 
 int /*<<< orphan*/  idi_48_gpio_get_multiple ; 
 int /*<<< orphan*/  idi_48_irq_handler ; 
 int /*<<< orphan*/  idi_48_irqchip ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/ * irq ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idi_48_probe(struct device *dev, unsigned int id)
{
	struct idi_48_gpio *idi48gpio;
	const char *const name = dev_name(dev);
	int err;

	idi48gpio = devm_kzalloc(dev, sizeof(*idi48gpio), GFP_KERNEL);
	if (!idi48gpio)
		return -ENOMEM;

	if (!devm_request_region(dev, base[id], IDI_48_EXTENT, name)) {
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + IDI_48_EXTENT);
		return -EBUSY;
	}

	idi48gpio->chip.label = name;
	idi48gpio->chip.parent = dev;
	idi48gpio->chip.owner = THIS_MODULE;
	idi48gpio->chip.base = -1;
	idi48gpio->chip.ngpio = IDI48_NGPIO;
	idi48gpio->chip.names = idi48_names;
	idi48gpio->chip.get_direction = idi_48_gpio_get_direction;
	idi48gpio->chip.direction_input = idi_48_gpio_direction_input;
	idi48gpio->chip.get = idi_48_gpio_get;
	idi48gpio->chip.get_multiple = idi_48_gpio_get_multiple;
	idi48gpio->base = base[id];

	raw_spin_lock_init(&idi48gpio->lock);
	spin_lock_init(&idi48gpio->ack_lock);

	err = devm_gpiochip_add_data(dev, &idi48gpio->chip, idi48gpio);
	if (err) {
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		return err;
	}

	/* Disable IRQ by default */
	outb(0, base[id] + 7);
	inb(base[id] + 7);

	err = gpiochip_irqchip_add(&idi48gpio->chip, &idi_48_irqchip, 0,
		handle_edge_irq, IRQ_TYPE_NONE);
	if (err) {
		dev_err(dev, "Could not add irqchip (%d)\n", err);
		return err;
	}

	err = devm_request_irq(dev, irq[id], idi_48_irq_handler, IRQF_SHARED,
		name, idi48gpio);
	if (err) {
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		return err;
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct adnp {int reg_shift; int* irq_enable; int* irq_level; int* irq_rise; int* irq_fall; int* irq_high; int* irq_low; TYPE_1__* client; int /*<<< orphan*/  irq_lock; struct gpio_chip gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIO_IER (struct adnp*) ; 
 scalar_t__ GPIO_PLR (struct adnp*) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  adnp_irq ; 
 int /*<<< orphan*/  adnp_irq_chip ; 
 int adnp_read (struct adnp*,scalar_t__,int*) ; 
 int adnp_write (struct adnp*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct adnp*) ; 
 int gpiochip_irqchip_add_nested (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_nested_irqchip (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adnp_irq_setup(struct adnp *adnp)
{
	unsigned int num_regs = 1 << adnp->reg_shift, i;
	struct gpio_chip *chip = &adnp->gpio;
	int err;

	mutex_init(&adnp->irq_lock);

	/*
	 * Allocate memory to keep track of the current level and trigger
	 * modes of the interrupts. To avoid multiple allocations, a single
	 * large buffer is allocated and pointers are setup to point at the
	 * corresponding offsets. For consistency, the layout of the buffer
	 * is chosen to match the register layout of the hardware in that
	 * each segment contains the corresponding bits for all interrupts.
	 */
	adnp->irq_enable = devm_kcalloc(chip->parent, num_regs, 6,
					GFP_KERNEL);
	if (!adnp->irq_enable)
		return -ENOMEM;

	adnp->irq_level = adnp->irq_enable + (num_regs * 1);
	adnp->irq_rise = adnp->irq_enable + (num_regs * 2);
	adnp->irq_fall = adnp->irq_enable + (num_regs * 3);
	adnp->irq_high = adnp->irq_enable + (num_regs * 4);
	adnp->irq_low = adnp->irq_enable + (num_regs * 5);

	for (i = 0; i < num_regs; i++) {
		/*
		 * Read the initial level of all pins to allow the emulation
		 * of edge triggered interrupts.
		 */
		err = adnp_read(adnp, GPIO_PLR(adnp) + i, &adnp->irq_level[i]);
		if (err < 0)
			return err;

		/* disable all interrupts */
		err = adnp_write(adnp, GPIO_IER(adnp) + i, 0);
		if (err < 0)
			return err;

		adnp->irq_enable[i] = 0x00;
	}

	err = devm_request_threaded_irq(chip->parent, adnp->client->irq,
					NULL, adnp_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(chip->parent), adnp);
	if (err != 0) {
		dev_err(chip->parent, "can't request IRQ#%d: %d\n",
			adnp->client->irq, err);
		return err;
	}

	err = gpiochip_irqchip_add_nested(chip,
					  &adnp_irq_chip,
					  0,
					  handle_simple_irq,
					  IRQ_TYPE_NONE);
	if (err) {
		dev_err(chip->parent,
			"could not connect irqchip to gpiochip\n");
		return err;
	}

	gpiochip_set_nested_irqchip(chip, &adnp_irq_chip, adnp->client->irq);

	return 0;
}
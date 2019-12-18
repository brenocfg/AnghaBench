#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct gpio_irq_chip {int num_parents; scalar_t__* parents; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  parent_handler; TYPE_2__* chip; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int ngpio; struct gpio_irq_chip irq; TYPE_4__* parent; int /*<<< orphan*/  owner; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; } ;
struct TYPE_10__ {TYPE_1__ gc; } ;
struct TYPE_9__ {char* name; void* irq_shutdown; int /*<<< orphan*/  irq_startup; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; void* irq_mask; } ;
struct altera_gpio_chip {scalar_t__ mapped_irq; int interrupt_trigger; TYPE_3__ mmchip; TYPE_2__ irq_chip; int /*<<< orphan*/  gpio_lock; } ;

/* Variables and functions */
 void* ALTERA_GPIO_MAX_NGPIO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  altera_gpio_direction_input ; 
 int /*<<< orphan*/  altera_gpio_direction_output ; 
 int /*<<< orphan*/  altera_gpio_get ; 
 int /*<<< orphan*/  altera_gpio_irq_edge_handler ; 
 int /*<<< orphan*/  altera_gpio_irq_leveL_high_handler ; 
 void* altera_gpio_irq_mask ; 
 int /*<<< orphan*/  altera_gpio_irq_set_type ; 
 int /*<<< orphan*/  altera_gpio_irq_startup ; 
 int /*<<< orphan*/  altera_gpio_irq_unmask ; 
 int /*<<< orphan*/  altera_gpio_set ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*,void*,void*) ; 
 scalar_t__* devm_kcalloc (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 struct altera_gpio_chip* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int of_mm_gpiochip_add_data (struct device_node*,TYPE_3__*,struct altera_gpio_chip*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct altera_gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int altera_gpio_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	int reg, ret;
	struct altera_gpio_chip *altera_gc;
	struct gpio_irq_chip *girq;

	altera_gc = devm_kzalloc(&pdev->dev, sizeof(*altera_gc), GFP_KERNEL);
	if (!altera_gc)
		return -ENOMEM;

	raw_spin_lock_init(&altera_gc->gpio_lock);

	if (of_property_read_u32(node, "altr,ngpio", &reg))
		/* By default assume maximum ngpio */
		altera_gc->mmchip.gc.ngpio = ALTERA_GPIO_MAX_NGPIO;
	else
		altera_gc->mmchip.gc.ngpio = reg;

	if (altera_gc->mmchip.gc.ngpio > ALTERA_GPIO_MAX_NGPIO) {
		dev_warn(&pdev->dev,
			"ngpio is greater than %d, defaulting to %d\n",
			ALTERA_GPIO_MAX_NGPIO, ALTERA_GPIO_MAX_NGPIO);
		altera_gc->mmchip.gc.ngpio = ALTERA_GPIO_MAX_NGPIO;
	}

	altera_gc->mmchip.gc.direction_input	= altera_gpio_direction_input;
	altera_gc->mmchip.gc.direction_output	= altera_gpio_direction_output;
	altera_gc->mmchip.gc.get		= altera_gpio_get;
	altera_gc->mmchip.gc.set		= altera_gpio_set;
	altera_gc->mmchip.gc.owner		= THIS_MODULE;
	altera_gc->mmchip.gc.parent		= &pdev->dev;

	altera_gc->mapped_irq = platform_get_irq(pdev, 0);

	if (altera_gc->mapped_irq < 0)
		goto skip_irq;

	if (of_property_read_u32(node, "altr,interrupt-type", &reg)) {
		dev_err(&pdev->dev,
			"altr,interrupt-type value not set in device tree\n");
		return -EINVAL;
	}
	altera_gc->interrupt_trigger = reg;

	altera_gc->irq_chip.name = "altera-gpio";
	altera_gc->irq_chip.irq_mask     = altera_gpio_irq_mask;
	altera_gc->irq_chip.irq_unmask   = altera_gpio_irq_unmask;
	altera_gc->irq_chip.irq_set_type = altera_gpio_irq_set_type;
	altera_gc->irq_chip.irq_startup  = altera_gpio_irq_startup;
	altera_gc->irq_chip.irq_shutdown = altera_gpio_irq_mask;

	girq = &altera_gc->mmchip.gc.irq;
	girq->chip = &altera_gc->irq_chip;
	if (altera_gc->interrupt_trigger == IRQ_TYPE_LEVEL_HIGH)
		girq->parent_handler = altera_gpio_irq_leveL_high_handler;
	else
		girq->parent_handler = altera_gpio_irq_edge_handler;
	girq->num_parents = 1;
	girq->parents = devm_kcalloc(&pdev->dev, 1, sizeof(*girq->parents),
				     GFP_KERNEL);
	if (!girq->parents)
		return -ENOMEM;
	girq->default_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->parents[0] = altera_gc->mapped_irq;

skip_irq:
	ret = of_mm_gpiochip_add_data(node, &altera_gc->mmchip, altera_gc);
	if (ret) {
		dev_err(&pdev->dev, "Failed adding memory mapped gpiochip\n");
		return ret;
	}

	platform_set_drvdata(pdev, altera_gc);

	return 0;
}
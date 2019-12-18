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
struct max77843_muic_info {int irq_adc; int irq_chg; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int virq; int irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  MAX77843_MUIC_IRQ_INT1_ADC 143 
#define  MAX77843_MUIC_IRQ_INT1_ADC1K 142 
#define  MAX77843_MUIC_IRQ_INT1_ADCERROR 141 
#define  MAX77843_MUIC_IRQ_INT2_CHGDETRUN 140 
#define  MAX77843_MUIC_IRQ_INT2_CHGTYP 139 
#define  MAX77843_MUIC_IRQ_INT2_DCDTMR 138 
#define  MAX77843_MUIC_IRQ_INT2_DXOVP 137 
#define  MAX77843_MUIC_IRQ_INT2_VBVOLT 136 
#define  MAX77843_MUIC_IRQ_INT3_DNRES 135 
#define  MAX77843_MUIC_IRQ_INT3_MPNACK 134 
#define  MAX77843_MUIC_IRQ_INT3_MRXBUFOW 133 
#define  MAX77843_MUIC_IRQ_INT3_MRXPERR 132 
#define  MAX77843_MUIC_IRQ_INT3_MRXRDY 131 
#define  MAX77843_MUIC_IRQ_INT3_MRXTRF 130 
#define  MAX77843_MUIC_IRQ_INT3_VBADC 129 
#define  MAX77843_MUIC_IRQ_INT3_VDNMON 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* max77843_muic_irqs ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t max77843_muic_irq_handler(int irq, void *data)
{
	struct max77843_muic_info *info = data;
	int i, irq_type = -1;

	for (i = 0; i < ARRAY_SIZE(max77843_muic_irqs); i++)
		if (irq == max77843_muic_irqs[i].virq)
			irq_type = max77843_muic_irqs[i].irq;

	switch (irq_type) {
	case MAX77843_MUIC_IRQ_INT1_ADC:
	case MAX77843_MUIC_IRQ_INT1_ADCERROR:
	case MAX77843_MUIC_IRQ_INT1_ADC1K:
		info->irq_adc = true;
		break;
	case MAX77843_MUIC_IRQ_INT2_CHGTYP:
	case MAX77843_MUIC_IRQ_INT2_CHGDETRUN:
	case MAX77843_MUIC_IRQ_INT2_DCDTMR:
	case MAX77843_MUIC_IRQ_INT2_DXOVP:
	case MAX77843_MUIC_IRQ_INT2_VBVOLT:
		info->irq_chg = true;
		break;
	case MAX77843_MUIC_IRQ_INT3_VBADC:
	case MAX77843_MUIC_IRQ_INT3_VDNMON:
	case MAX77843_MUIC_IRQ_INT3_DNRES:
	case MAX77843_MUIC_IRQ_INT3_MPNACK:
	case MAX77843_MUIC_IRQ_INT3_MRXBUFOW:
	case MAX77843_MUIC_IRQ_INT3_MRXTRF:
	case MAX77843_MUIC_IRQ_INT3_MRXPERR:
	case MAX77843_MUIC_IRQ_INT3_MRXRDY:
		break;
	default:
		dev_err(info->dev, "Cannot recognize IRQ(%d)\n", irq_type);
		break;
	}

	schedule_work(&info->irq_work);

	return IRQ_HANDLED;
}
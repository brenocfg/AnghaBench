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
struct rt8973a_muic_info {int num_muic_irqs; int irq_attach; int irq_detach; int irq_ovp; int irq_otp; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  dev; TYPE_1__* muic_irqs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int virq; int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  RT8973A_INT1_ADC_CHG 142 
#define  RT8973A_INT1_ATTACH 141 
#define  RT8973A_INT1_CHGDET 140 
#define  RT8973A_INT1_CONNECT 139 
#define  RT8973A_INT1_DCD_T 138 
#define  RT8973A_INT1_DETACH 137 
#define  RT8973A_INT1_OTP 136 
#define  RT8973A_INT1_OVP 135 
#define  RT8973A_INT2_OCP 134 
#define  RT8973A_INT2_OCP_LATCH 133 
#define  RT8973A_INT2_OTP_FET 132 
#define  RT8973A_INT2_OVP_FET 131 
#define  RT8973A_INT2_OVP_OCP 130 
#define  RT8973A_INT2_POR 129 
#define  RT8973A_INT2_UVLO 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rt8973a_muic_irq_handler(int irq, void *data)
{
	struct rt8973a_muic_info *info = data;
	int i, irq_type = -1;

	for (i = 0; i < info->num_muic_irqs; i++)
		if (irq == info->muic_irqs[i].virq)
			irq_type = info->muic_irqs[i].irq;

	switch (irq_type) {
	case RT8973A_INT1_ATTACH:
		info->irq_attach = true;
		break;
	case RT8973A_INT1_DETACH:
		info->irq_detach = true;
		break;
	case RT8973A_INT1_OVP:
		info->irq_ovp = true;
		break;
	case RT8973A_INT1_OTP:
		info->irq_otp = true;
		break;
	case RT8973A_INT1_CHGDET:
	case RT8973A_INT1_DCD_T:
	case RT8973A_INT1_CONNECT:
	case RT8973A_INT1_ADC_CHG:
	case RT8973A_INT2_UVLO:
	case RT8973A_INT2_POR:
	case RT8973A_INT2_OTP_FET:
	case RT8973A_INT2_OVP_FET:
	case RT8973A_INT2_OCP_LATCH:
	case RT8973A_INT2_OCP:
	case RT8973A_INT2_OVP_OCP:
	default:
		dev_dbg(info->dev,
			"Cannot handle this interrupt (%d)\n", irq_type);
		break;
	}

	schedule_work(&info->irq_work);

	return IRQ_HANDLED;
}
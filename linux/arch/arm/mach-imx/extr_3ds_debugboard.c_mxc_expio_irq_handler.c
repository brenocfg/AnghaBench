#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct irq_desc {TYPE_2__ irq_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* irq_unmask ) (TYPE_2__*) ;int /*<<< orphan*/  (* irq_ack ) (TYPE_2__*) ;int /*<<< orphan*/  (* irq_mask ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ INTR_MASK_REG ; 
 scalar_t__ INTR_STATUS_REG ; 
 scalar_t__ brd_io ; 
 int /*<<< orphan*/  domain ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int imx_readw (scalar_t__) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

__attribute__((used)) static void mxc_expio_irq_handler(struct irq_desc *desc)
{
	u32 imr_val;
	u32 int_valid;
	u32 expio_irq;

	/* irq = gpio irq number */
	desc->irq_data.chip->irq_mask(&desc->irq_data);

	imr_val = imx_readw(brd_io + INTR_MASK_REG);
	int_valid = imx_readw(brd_io + INTR_STATUS_REG) & ~imr_val;

	expio_irq = 0;
	for (; int_valid != 0; int_valid >>= 1, expio_irq++) {
		if ((int_valid & 1) == 0)
			continue;
		generic_handle_irq(irq_find_mapping(domain, expio_irq));
	}

	desc->irq_data.chip->irq_ack(&desc->irq_data);
	desc->irq_data.chip->irq_unmask(&desc->irq_data);
}
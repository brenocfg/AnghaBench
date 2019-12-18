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
struct fwnode_handle {int dummy; } ;
struct acpi_resource_irq {size_t interrupt_count; int /*<<< orphan*/  shareable; int /*<<< orphan*/  polarity; int /*<<< orphan*/  triggering; int /*<<< orphan*/ * interrupts; } ;
struct acpi_resource_extended_irq {size_t interrupt_count; int /*<<< orphan*/  shareable; int /*<<< orphan*/  polarity; int /*<<< orphan*/  triggering; int /*<<< orphan*/ * interrupts; int /*<<< orphan*/  resource_source; int /*<<< orphan*/  producer_consumer; } ;
struct TYPE_2__ {struct acpi_resource_extended_irq extended_irq; struct acpi_resource_irq irq; } ;
struct acpi_resource {int type; TYPE_1__ data; } ;
struct acpi_irq_parse_one_ctx {size_t index; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PRODUCER ; 
#define  ACPI_RESOURCE_TYPE_EXTENDED_IRQ 129 
#define  ACPI_RESOURCE_TYPE_IRQ 128 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 struct fwnode_handle* acpi_get_irq_source_fwhandle (int /*<<< orphan*/ *) ; 
 struct fwnode_handle* acpi_gsi_domain_id ; 
 int /*<<< orphan*/  acpi_irq_parse_one_match (struct fwnode_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_irq_parse_one_ctx*) ; 

__attribute__((used)) static acpi_status acpi_irq_parse_one_cb(struct acpi_resource *ares,
					 void *context)
{
	struct acpi_irq_parse_one_ctx *ctx = context;
	struct acpi_resource_irq *irq;
	struct acpi_resource_extended_irq *eirq;
	struct fwnode_handle *fwnode;

	switch (ares->type) {
	case ACPI_RESOURCE_TYPE_IRQ:
		irq = &ares->data.irq;
		if (ctx->index >= irq->interrupt_count) {
			ctx->index -= irq->interrupt_count;
			return AE_OK;
		}
		fwnode = acpi_gsi_domain_id;
		acpi_irq_parse_one_match(fwnode, irq->interrupts[ctx->index],
					 irq->triggering, irq->polarity,
					 irq->shareable, ctx);
		return AE_CTRL_TERMINATE;
	case ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		eirq = &ares->data.extended_irq;
		if (eirq->producer_consumer == ACPI_PRODUCER)
			return AE_OK;
		if (ctx->index >= eirq->interrupt_count) {
			ctx->index -= eirq->interrupt_count;
			return AE_OK;
		}
		fwnode = acpi_get_irq_source_fwhandle(&eirq->resource_source);
		acpi_irq_parse_one_match(fwnode, eirq->interrupts[ctx->index],
					 eirq->triggering, eirq->polarity,
					 eirq->shareable, ctx);
		return AE_CTRL_TERMINATE;
	}

	return AE_OK;
}
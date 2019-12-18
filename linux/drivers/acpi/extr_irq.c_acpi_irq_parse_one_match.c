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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fwnode_handle {int dummy; } ;
struct acpi_irq_parse_one_ctx {TYPE_1__* fwspec; int /*<<< orphan*/ * res_flags; scalar_t__ rc; } ;
struct TYPE_2__ {int param_count; int /*<<< orphan*/ * param; struct fwnode_handle* fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_dev_get_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dev_irq_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void acpi_irq_parse_one_match(struct fwnode_handle *fwnode,
					    u32 hwirq, u8 triggering,
					    u8 polarity, u8 shareable,
					    struct acpi_irq_parse_one_ctx *ctx)
{
	if (!fwnode)
		return;
	ctx->rc = 0;
	*ctx->res_flags = acpi_dev_irq_flags(triggering, polarity, shareable);
	ctx->fwspec->fwnode = fwnode;
	ctx->fwspec->param[0] = hwirq;
	ctx->fwspec->param[1] = acpi_dev_get_irq_type(triggering, polarity);
	ctx->fwspec->param_count = 2;
}
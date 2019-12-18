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
struct dma_chan {int dummy; } ;
struct acpi_dma_spec {int dummy; } ;
struct acpi_dma_filter_info {int /*<<< orphan*/  filter_fn; int /*<<< orphan*/  dma_cap; } ;
struct acpi_dma {struct acpi_dma_filter_info* data; } ;

/* Variables and functions */
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_dma_spec*) ; 

struct dma_chan *acpi_dma_simple_xlate(struct acpi_dma_spec *dma_spec,
		struct acpi_dma *adma)
{
	struct acpi_dma_filter_info *info = adma->data;

	if (!info || !info->filter_fn)
		return NULL;

	return dma_request_channel(info->dma_cap, info->filter_fn, dma_spec);
}
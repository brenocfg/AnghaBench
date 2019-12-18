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
struct acpi_dma_spec {scalar_t__ slave_id; int /*<<< orphan*/  dev; } ;
struct acpi_dma {scalar_t__ base_request_line; scalar_t__ end_request_line; int /*<<< orphan*/  dev; } ;

/* Variables and functions */

__attribute__((used)) static int acpi_dma_update_dma_spec(struct acpi_dma *adma,
		struct acpi_dma_spec *dma_spec)
{
	/* Set link to the DMA controller device */
	dma_spec->dev = adma->dev;

	/* Check if the request line range is available */
	if (adma->base_request_line == 0 && adma->end_request_line == 0)
		return 0;

	/* Check if slave_id falls to the range */
	if (dma_spec->slave_id < adma->base_request_line ||
	    dma_spec->slave_id > adma->end_request_line)
		return -1;

	/*
	 * Here we adjust slave_id. It should be a relative number to the base
	 * request line.
	 */
	dma_spec->slave_id -= adma->base_request_line;

	return 1;
}
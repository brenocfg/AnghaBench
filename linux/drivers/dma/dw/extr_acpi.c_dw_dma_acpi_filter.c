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
struct dw_dma_slave {int p_master; int /*<<< orphan*/  m_master; int /*<<< orphan*/  dst_id; int /*<<< orphan*/  src_id; int /*<<< orphan*/  dma_dev; } ;
struct dma_chan {int dummy; } ;
struct acpi_dma_spec {int /*<<< orphan*/  slave_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dw_dma_filter (struct dma_chan*,struct dw_dma_slave*) ; 

__attribute__((used)) static bool dw_dma_acpi_filter(struct dma_chan *chan, void *param)
{
	struct acpi_dma_spec *dma_spec = param;
	struct dw_dma_slave slave = {
		.dma_dev = dma_spec->dev,
		.src_id = dma_spec->slave_id,
		.dst_id = dma_spec->slave_id,
		.m_master = 0,
		.p_master = 1,
	};

	return dw_dma_filter(chan, &slave);
}
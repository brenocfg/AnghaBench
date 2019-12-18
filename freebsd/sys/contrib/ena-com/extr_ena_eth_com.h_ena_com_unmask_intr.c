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
struct ena_eth_io_intr_reg {int /*<<< orphan*/  intr_control; } ;
struct ena_com_io_cq {int /*<<< orphan*/  unmask_reg; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ena_com_unmask_intr(struct ena_com_io_cq *io_cq,
				       struct ena_eth_io_intr_reg *intr_reg)
{
	ENA_REG_WRITE32(io_cq->bus, intr_reg->intr_control, io_cq->unmask_reg);
}
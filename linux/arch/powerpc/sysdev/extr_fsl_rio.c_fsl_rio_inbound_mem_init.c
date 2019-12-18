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
struct rio_priv {TYPE_1__* inb_atmu_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  riwar; } ;

/* Variables and functions */
 int RIO_INB_ATMU_COUNT ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_rio_inbound_mem_init(struct rio_priv *priv)
{
	int i;

	/* close inbound windows */
	for (i = 0; i < RIO_INB_ATMU_COUNT; i++)
		out_be32(&priv->inb_atmu_regs[i].riwar, 0);
}
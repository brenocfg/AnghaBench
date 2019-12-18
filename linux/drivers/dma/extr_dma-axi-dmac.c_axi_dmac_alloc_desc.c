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
struct axi_dmac_desc {unsigned int num_sgs; TYPE_1__* sg; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_DMAC_SG_UNUSED ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 struct axi_dmac_desc* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg ; 
 int /*<<< orphan*/  struct_size (struct axi_dmac_desc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct axi_dmac_desc *axi_dmac_alloc_desc(unsigned int num_sgs)
{
	struct axi_dmac_desc *desc;
	unsigned int i;

	desc = kzalloc(struct_size(desc, sg, num_sgs), GFP_NOWAIT);
	if (!desc)
		return NULL;

	for (i = 0; i < num_sgs; i++)
		desc->sg[i].id = AXI_DMAC_SG_UNUSED;

	desc->num_sgs = num_sgs;

	return desc;
}
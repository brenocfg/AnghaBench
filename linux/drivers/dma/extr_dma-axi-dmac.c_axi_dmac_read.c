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
struct axi_dmac {scalar_t__ base; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 

__attribute__((used)) static int axi_dmac_read(struct axi_dmac *axi_dmac, unsigned int reg)
{
	return readl(axi_dmac->base + reg);
}
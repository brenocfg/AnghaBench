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
typedef  int /*<<< orphan*/  u32 ;
struct ppc440spe_adma_desc_slot {TYPE_1__* hw_next; } ;
struct ppc440spe_adma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 ppc440spe_desc_get_link(struct ppc440spe_adma_desc_slot *desc,
					struct ppc440spe_adma_chan *chan)
{
	if (!desc->hw_next)
		return 0;

	return desc->hw_next->phys;
}
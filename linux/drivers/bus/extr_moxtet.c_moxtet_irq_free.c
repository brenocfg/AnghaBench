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
struct TYPE_2__ {int exists; int /*<<< orphan*/  domain; } ;
struct moxtet {TYPE_1__ irq; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MOXTET_NIRQS ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void moxtet_irq_free(struct moxtet *moxtet)
{
	int i, irq;

	for (i = 0; i < MOXTET_NIRQS; ++i) {
		if (moxtet->irq.exists & BIT(i)) {
			irq = irq_find_mapping(moxtet->irq.domain, i);
			irq_dispose_mapping(irq);
		}
	}

	irq_domain_remove(moxtet->irq.domain);
}
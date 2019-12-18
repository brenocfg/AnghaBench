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
typedef  int /*<<< orphan*/  u_int ;
struct powerpc_intr {int /*<<< orphan*/  priv; int /*<<< orphan*/  intline; int /*<<< orphan*/ * pic; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_UNMASK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct powerpc_intr* intr_lookup (int /*<<< orphan*/ ) ; 

void
powerpc_intr_unmask(u_int irq)
{
	struct powerpc_intr *i;

	i = intr_lookup(irq);
	if (i == NULL || i->pic == NULL)
		return;

	PIC_UNMASK(i->pic, i->intline, i->priv);
}
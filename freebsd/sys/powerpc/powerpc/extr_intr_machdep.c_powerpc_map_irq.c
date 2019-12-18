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
typedef  scalar_t__ u_int ;
struct powerpc_intr {scalar_t__ irq; scalar_t__ intline; int /*<<< orphan*/ * pic; } ;
struct pic {scalar_t__ irqs; scalar_t__ ipis; scalar_t__ base; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int npics ; 
 struct pic* piclist ; 
 int /*<<< orphan*/ * root_pic ; 

__attribute__((used)) static int
powerpc_map_irq(struct powerpc_intr *i)
{
	struct pic *p;
	u_int cnt;
	int idx;

	for (idx = 0; idx < npics; idx++) {
		p = &piclist[idx];
		cnt = p->irqs + p->ipis;
		if (i->irq >= p->base && i->irq < p->base + cnt)
			break;
	}
	if (idx == npics)
		return (EINVAL);

	i->intline = i->irq - p->base;
	i->pic = p->dev;

	/* Try a best guess if that failed */
	if (i->pic == NULL)
		i->pic = root_pic;

	return (0);
}
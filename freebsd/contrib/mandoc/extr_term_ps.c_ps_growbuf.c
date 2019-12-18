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
struct termp {TYPE_1__* ps; } ;
struct TYPE_2__ {scalar_t__ psmargcur; scalar_t__ psmargsz; int /*<<< orphan*/  psmarg; } ;

/* Variables and functions */
 size_t PS_BUFSLOP ; 
 int /*<<< orphan*/  mandoc_realloc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ps_growbuf(struct termp *p, size_t sz)
{
	if (p->ps->psmargcur + sz <= p->ps->psmargsz)
		return;

	if (sz < PS_BUFSLOP)
		sz = PS_BUFSLOP;

	p->ps->psmargsz += sz;
	p->ps->psmarg = mandoc_realloc(p->ps->psmarg, p->ps->psmargsz);
}
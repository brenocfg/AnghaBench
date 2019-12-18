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
struct TYPE_2__ {struct TYPE_2__* pdfobjs; struct TYPE_2__* psmarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  term_free (struct termp*) ; 

void
pspdf_free(void *arg)
{
	struct termp	*p;

	p = (struct termp *)arg;

	free(p->ps->psmarg);
	free(p->ps->pdfobjs);

	free(p->ps);
	term_free(p);
}
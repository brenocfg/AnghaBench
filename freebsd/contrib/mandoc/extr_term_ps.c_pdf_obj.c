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
struct TYPE_2__ {size_t pdfobjsz; int /*<<< orphan*/  pdfbytes; int /*<<< orphan*/ * pdfobjs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * mandoc_reallocarray (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  ps_printf (struct termp*,char*,size_t) ; 

__attribute__((used)) static void
pdf_obj(struct termp *p, size_t obj)
{

	assert(obj > 0);

	if ((obj - 1) >= p->ps->pdfobjsz) {
		p->ps->pdfobjsz = obj + 128;
		p->ps->pdfobjs = mandoc_reallocarray(p->ps->pdfobjs,
		    p->ps->pdfobjsz, sizeof(size_t));
	}

	p->ps->pdfobjs[(int)obj - 1] = p->ps->pdfbytes;
	ps_printf(p, "%zu 0 obj\n", obj);
}
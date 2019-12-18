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
struct termp {scalar_t__ type; TYPE_1__* ps; } ;
struct TYPE_2__ {int flags; char last; size_t pages; size_t pdfbody; size_t pdfbytes; int /*<<< orphan*/ * pdfobjs; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 scalar_t__ AFM2PNT (struct termp*,int /*<<< orphan*/ ) ; 
 int PS_NEWPAGE ; 
 scalar_t__ TERMTYPE_PS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pdf_obj (struct termp*,size_t) ; 
 int /*<<< orphan*/  ps_closepage (struct termp*) ; 
 int /*<<< orphan*/  ps_pclose (struct termp*) ; 
 int /*<<< orphan*/  ps_plast (struct termp*) ; 
 int /*<<< orphan*/  ps_printf (struct termp*,char*,...) ; 

__attribute__((used)) static void
ps_end(struct termp *p)
{
	size_t		 i, xref, base;

	ps_plast(p);
	ps_pclose(p);

	/*
	 * At the end of the file, do one last showpage.  This is the
	 * same behaviour as groff(1) and works for multiple pages as
	 * well as just one.
	 */

	if ( ! (PS_NEWPAGE & p->ps->flags)) {
		assert(0 == p->ps->flags);
		assert('\0' == p->ps->last);
		ps_closepage(p);
	}

	if (TERMTYPE_PS == p->type) {
		ps_printf(p, "%%%%Trailer\n");
		ps_printf(p, "%%%%Pages: %zu\n", p->ps->pages);
		ps_printf(p, "%%%%EOF\n");
		return;
	}

	pdf_obj(p, 2);
	ps_printf(p, "<<\n/Type /Pages\n");
	ps_printf(p, "/MediaBox [0 0 %zu %zu]\n",
			(size_t)AFM2PNT(p, p->ps->width),
			(size_t)AFM2PNT(p, p->ps->height));

	ps_printf(p, "/Count %zu\n", p->ps->pages);
	ps_printf(p, "/Kids [");

	for (i = 0; i < p->ps->pages; i++)
		ps_printf(p, " %zu 0 R", i * 4 + p->ps->pdfbody + 3);

	base = (p->ps->pages - 1) * 4 + p->ps->pdfbody + 4;

	ps_printf(p, "]\n>>\nendobj\n");
	pdf_obj(p, base);
	ps_printf(p, "<<\n");
	ps_printf(p, "/Type /Catalog\n");
	ps_printf(p, "/Pages 2 0 R\n");
	ps_printf(p, ">>\nendobj\n");
	xref = p->ps->pdfbytes;
	ps_printf(p, "xref\n");
	ps_printf(p, "0 %zu\n", base + 1);
	ps_printf(p, "0000000000 65535 f \n");

	for (i = 0; i < base; i++)
		ps_printf(p, "%.10zu 00000 n \n",
		    p->ps->pdfobjs[(int)i]);

	ps_printf(p, "trailer\n");
	ps_printf(p, "<<\n");
	ps_printf(p, "/Size %zu\n", base + 1);
	ps_printf(p, "/Root %zu 0 R\n", base);
	ps_printf(p, "/Info 1 0 R\n");
	ps_printf(p, ">>\n");
	ps_printf(p, "startxref\n");
	ps_printf(p, "%zu\n", xref);
	ps_printf(p, "%%%%EOF\n");
}
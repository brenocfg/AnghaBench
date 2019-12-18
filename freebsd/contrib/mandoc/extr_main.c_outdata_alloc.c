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
struct curparse {int outtype; int /*<<< orphan*/  outopts; int /*<<< orphan*/  outdata; } ;

/* Variables and functions */
#define  OUTT_ASCII 133 
#define  OUTT_HTML 132 
#define  OUTT_LOCALE 131 
#define  OUTT_PDF 130 
#define  OUTT_PS 129 
#define  OUTT_UTF8 128 
 int /*<<< orphan*/  ascii_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  html_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locale_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
outdata_alloc(struct curparse *curp)
{
	switch (curp->outtype) {
	case OUTT_HTML:
		curp->outdata = html_alloc(curp->outopts);
		break;
	case OUTT_UTF8:
		curp->outdata = utf8_alloc(curp->outopts);
		break;
	case OUTT_LOCALE:
		curp->outdata = locale_alloc(curp->outopts);
		break;
	case OUTT_ASCII:
		curp->outdata = ascii_alloc(curp->outopts);
		break;
	case OUTT_PDF:
		curp->outdata = pdf_alloc(curp->outopts);
		break;
	case OUTT_PS:
		curp->outdata = ps_alloc(curp->outopts);
		break;
	default:
		break;
	}
}
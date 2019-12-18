#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tbl_span {scalar_t__ pos; TYPE_1__* opts; } ;
struct TYPE_4__ {int /*<<< orphan*/  sulen; int /*<<< orphan*/  slen; int /*<<< orphan*/  len; int /*<<< orphan*/ * cols; } ;
struct html {int /*<<< orphan*/ * tblt; TYPE_2__ tbl; } ;
struct TYPE_3__ {int opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_TABLE ; 
 int TBL_OPT_ALLBOX ; 
 int TBL_OPT_BOX ; 
 int TBL_OPT_DBOX ; 
 scalar_t__ TBL_SPAN_DHORIZ ; 
 scalar_t__ TBL_SPAN_HORIZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  html_close_paragraph (struct html*) ; 
 int /*<<< orphan*/  html_tbl_len ; 
 int /*<<< orphan*/  html_tbl_strlen ; 
 int /*<<< orphan*/  html_tbl_sulen ; 
 int /*<<< orphan*/ * print_otag (struct html*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  tblcalc (TYPE_2__*,struct tbl_span const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
html_tblopen(struct html *h, const struct tbl_span *sp)
{
	html_close_paragraph(h);
	if (h->tbl.cols == NULL) {
		h->tbl.len = html_tbl_len;
		h->tbl.slen = html_tbl_strlen;
		h->tbl.sulen = html_tbl_sulen;
		tblcalc(&h->tbl, sp, 0, 0);
	}
	assert(NULL == h->tblt);
	h->tblt = print_otag(h, TAG_TABLE, "c?ss", "tbl",
	    "border",
		sp->opts->opts & TBL_OPT_ALLBOX ? "1" : NULL,
	    "border-style",
		sp->opts->opts & TBL_OPT_DBOX ? "double" :
		sp->opts->opts & TBL_OPT_BOX ? "solid" : NULL,
	    "border-top-style",
		sp->pos == TBL_SPAN_DHORIZ ? "double" :
		sp->pos == TBL_SPAN_HORIZ ? "solid" : NULL);
}
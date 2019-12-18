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
typedef  size_t u_int ;
struct unicx {size_t errcnt; TYPE_1__* err; int /*<<< orphan*/  tabsiz; int /*<<< orphan*/  multiline; int /*<<< orphan*/  cause_hard; int /*<<< orphan*/  bearer_hard; int /*<<< orphan*/  git_hard; int /*<<< orphan*/  pnni; int /*<<< orphan*/  q2932; } ;
struct TYPE_2__ {size_t err; size_t act; scalar_t__ man; int /*<<< orphan*/  ie; } ;

/* Variables and functions */
#define  UNI_IERR_ACC 132 
#define  UNI_IERR_BAD 131 
#define  UNI_IERR_LEN 130 
#define  UNI_IERR_MIS 129 
#define  UNI_IERR_UNK 128 
 int /*<<< orphan*/  uni_print_init (char*,size_t,struct unicx*) ; 
 int /*<<< orphan*/  uni_printf (struct unicx*,char*,...) ; 
 int /*<<< orphan*/  uni_putc (char,struct unicx*) ; 

void
uni_print_cx(char *buf, size_t size, struct unicx *cx)
{
	static const char *acttab[] = {
		"clr",	/* 0x00 */
		"ign",	/* 0x01 */
		"rep",	/* 0x02 */
		"x03",	/* 0x03 */
		"x04",	/* 0x04 */
		"mig",	/* 0x05 */
		"mrp",	/* 0x06 */
		"x07",	/* 0x07 */
		"def",	/* 0x08 */
	};

	static const char *errtab[] = {
		[UNI_IERR_UNK] = "unk",	/* unknown IE */
		[UNI_IERR_LEN] = "len",	/* length error */
		[UNI_IERR_BAD] = "bad",	/* content error */
		[UNI_IERR_ACC] = "acc",	/* access element discarded */
		[UNI_IERR_MIS] = "mis",	/* missing IE */
	};

	u_int i;

	uni_print_init(buf, size, cx);

	uni_printf(cx, "q2932		%d\n", cx->q2932);
	uni_printf(cx, "pnni		%d\n", cx->pnni);
	uni_printf(cx, "git_hard	%d\n", cx->git_hard);
	uni_printf(cx, "bearer_hard	%d\n", cx->bearer_hard);
	uni_printf(cx, "cause_hard	%d\n", cx->cause_hard);

	uni_printf(cx, "multiline	%d\n", cx->multiline);
	uni_printf(cx, "tabsiz		%d\n", cx->tabsiz);

	uni_printf(cx, "errcnt		%d (", cx->errcnt);
	for(i = 0; i < cx->errcnt; i++) {
		uni_printf(cx, "%02x[%s,%s%s]", cx->err[i].ie,
		    errtab[cx->err[i].err], acttab[cx->err[i].act],
		    cx->err[i].man ? ",M" : "");
		if(i != cx->errcnt - 1)
			uni_putc(' ', cx);
	}
	uni_printf(cx, ")\n");
}
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
struct roff_meta {char* title; char* msec; char* vol; char* arch; char* os; char* date; TYPE_1__* first; } ;
struct TYPE_2__ {int /*<<< orphan*/  child; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_Sm ; 
 int /*<<< orphan*/  MD_sp ; 
 int /*<<< orphan*/  MD_spc ; 
 int /*<<< orphan*/  md_nodelist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_word (char*) ; 
 int /*<<< orphan*/  outflags ; 
 int /*<<< orphan*/  putchar (char) ; 

void
markdown_mdoc(void *arg, const struct roff_meta *mdoc)
{
	outflags = MD_Sm;
	md_word(mdoc->title);
	if (mdoc->msec != NULL) {
		outflags &= ~MD_spc;
		md_word("(");
		md_word(mdoc->msec);
		md_word(")");
	}
	md_word("-");
	md_word(mdoc->vol);
	if (mdoc->arch != NULL) {
		md_word("(");
		md_word(mdoc->arch);
		md_word(")");
	}
	outflags |= MD_sp;

	md_nodelist(mdoc->first->child);

	outflags |= MD_sp;
	md_word(mdoc->os);
	md_word("-");
	md_word(mdoc->date);
	putchar('\n');
}
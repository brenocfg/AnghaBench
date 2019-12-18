#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct termp {size_t defindent; scalar_t__ synopsisonly; int /*<<< orphan*/  flags; int /*<<< orphan*/  defrmargin; int /*<<< orphan*/  maxrmargin; TYPE_1__* tcol; } ;
struct roff_node {scalar_t__ tok; scalar_t__ type; TYPE_4__* child; int /*<<< orphan*/  string; struct roff_node* next; } ;
struct roff_meta {TYPE_2__* first; } ;
struct mtermp {size_t lmargincur; int pardist; void* offset; void** lmargin; } ;
typedef  int /*<<< orphan*/  mt ;
struct TYPE_8__ {TYPE_3__* next; struct roff_node* child; } ;
struct TYPE_7__ {struct roff_node* child; } ;
struct TYPE_6__ {struct roff_node* child; } ;
struct TYPE_5__ {int /*<<< orphan*/  rmargin; } ;

/* Variables and functions */
 scalar_t__ MAN_SH ; 
 scalar_t__ ROFFT_TEXT ; 
 int /*<<< orphan*/  TERMP_NOSPACE ; 
 int /*<<< orphan*/  memset (struct mtermp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_man_foot ; 
 int /*<<< orphan*/  print_man_head ; 
 int /*<<< orphan*/  print_man_nodelist (struct termp*,struct mtermp*,struct roff_node*,struct roff_meta const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  term_begin (struct termp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct roff_meta const*) ; 
 int /*<<< orphan*/  term_end (struct termp*) ; 
 void* term_len (struct termp*,int) ; 
 int /*<<< orphan*/  term_newln (struct termp*) ; 
 int /*<<< orphan*/  term_tab_set (struct termp*,char*) ; 

void
terminal_man(void *arg, const struct roff_meta *man)
{
	struct mtermp		 mt;
	struct termp		*p;
	struct roff_node	*n, *nc, *nn;
	size_t			 save_defindent;

	p = (struct termp *)arg;
	save_defindent = p->defindent;
	if (p->synopsisonly == 0 && p->defindent == 0)
		p->defindent = 7;
	p->tcol->rmargin = p->maxrmargin = p->defrmargin;
	term_tab_set(p, NULL);
	term_tab_set(p, "T");
	term_tab_set(p, ".5i");

	memset(&mt, 0, sizeof(mt));
	mt.lmargin[mt.lmargincur] = term_len(p, p->defindent);
	mt.offset = term_len(p, p->defindent);
	mt.pardist = 1;

	n = man->first->child;
	if (p->synopsisonly) {
		for (nn = NULL; n != NULL; n = n->next) {
			if (n->tok != MAN_SH)
				continue;
			nc = n->child->child;
			if (nc->type != ROFFT_TEXT)
				continue;
			if (strcmp(nc->string, "SYNOPSIS") == 0)
				break;
			if (nn == NULL && strcmp(nc->string, "NAME") == 0)
				nn = n;
		}
		if (n == NULL)
			n = nn;
		p->flags |= TERMP_NOSPACE;
		if (n != NULL && (n = n->child->next->child) != NULL)
			print_man_nodelist(p, &mt, n, man);
		term_newln(p);
	} else {
		term_begin(p, print_man_head, print_man_foot, man);
		p->flags |= TERMP_NOSPACE;
		if (n != NULL)
			print_man_nodelist(p, &mt, n, man);
		term_end(p);
	}
	p->defindent = save_defindent;
}
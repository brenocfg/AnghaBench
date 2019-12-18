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
struct roff_node {scalar_t__ type; char* string; struct roff_node* next; } ;
struct roff_meta {char* title; char* msec; char* date; char* os; char* vol; TYPE_1__* first; } ;
struct TYPE_4__ {int size; char* head; char* tail; } ;
struct TYPE_3__ {struct roff_node* child; } ;

/* Variables and functions */
 int MMAN_Sm ; 
 int MMAN_nl ; 
 scalar_t__ ROFFT_COMMENT ; 
 TYPE_2__ fontqueue ; 
 char* mandoc_malloc (int) ; 
 int outflags ; 
 int /*<<< orphan*/  print_node (struct roff_meta const*,struct roff_node*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

void
man_mdoc(void *arg, const struct roff_meta *mdoc)
{
	struct roff_node *n;

	printf(".\\\" Automatically generated from an mdoc input file."
	    "  Do not edit.\n");
	for (n = mdoc->first->child; n != NULL; n = n->next) {
		if (n->type != ROFFT_COMMENT)
			break;
		printf(".\\\"%s\n", n->string);
	}

	printf(".TH \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
	    mdoc->title, (mdoc->msec == NULL ? "" : mdoc->msec),
	    mdoc->date, mdoc->os, mdoc->vol);

	/* Disable hyphenation and if nroff, disable justification. */
	printf(".nh\n.if n .ad l");

	outflags = MMAN_nl | MMAN_Sm;
	if (0 == fontqueue.size) {
		fontqueue.size = 8;
		fontqueue.head = fontqueue.tail = mandoc_malloc(8);
		*fontqueue.tail = 'R';
	}
	for (; n != NULL; n = n->next)
		print_node(mdoc, n);
	putchar('\n');
}
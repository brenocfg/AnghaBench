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
struct roff_node {int type; char* string; size_t tok; int flags; int line; int pos; struct roff_node* next; struct roff_node* child; TYPE_1__* eqn; scalar_t__ span; } ;
struct TYPE_2__ {int /*<<< orphan*/  first; } ;

/* Variables and functions */
 int NODE_DELIMC ; 
 int NODE_EOS ; 
 int NODE_LINE ; 
 int NODE_NOFILL ; 
#define  ROFFT_BLOCK 136 
#define  ROFFT_BODY 135 
#define  ROFFT_COMMENT 134 
#define  ROFFT_ELEM 133 
#define  ROFFT_EQN 132 
#define  ROFFT_HEAD 131 
#define  ROFFT_ROOT 130 
#define  ROFFT_TBL 129 
#define  ROFFT_TEXT 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_box (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_span (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char** roff_name ; 

__attribute__((used)) static void
print_man(const struct roff_node *n, int indent)
{
	const char	 *p, *t;
	int		  i;

	if (n == NULL)
		return;

	t = p = NULL;

	switch (n->type) {
	case ROFFT_ROOT:
		t = "root";
		break;
	case ROFFT_ELEM:
		t = "elem";
		break;
	case ROFFT_TEXT:
		t = "text";
		break;
	case ROFFT_COMMENT:
		t = "comment";
		break;
	case ROFFT_BLOCK:
		t = "block";
		break;
	case ROFFT_HEAD:
		t = "head";
		break;
	case ROFFT_BODY:
		t = "body";
		break;
	case ROFFT_TBL:
		break;
	case ROFFT_EQN:
		t = "eqn";
		break;
	default:
		abort();
	}

	switch (n->type) {
	case ROFFT_TEXT:
	case ROFFT_COMMENT:
		p = n->string;
		break;
	case ROFFT_ELEM:
	case ROFFT_BLOCK:
	case ROFFT_HEAD:
	case ROFFT_BODY:
		p = roff_name[n->tok];
		break;
	case ROFFT_ROOT:
		p = "root";
		break;
	case ROFFT_TBL:
		break;
	case ROFFT_EQN:
		p = "EQ";
		break;
	default:
		abort();
	}

	if (n->span) {
		assert(NULL == p && NULL == t);
		print_span(n->span, indent);
	} else {
		for (i = 0; i < indent; i++)
			putchar(' ');
		printf("%s (%s) ", p, t);
		if (n->flags & NODE_LINE)
			putchar('*');
		printf("%d:%d", n->line, n->pos + 1);
		if (n->flags & NODE_DELIMC)
			putchar(')');
		if (n->flags & NODE_EOS)
			putchar('.');
		if (n->flags & NODE_NOFILL)
			printf(" NOFILL");
		putchar('\n');
	}

	if (n->eqn)
		print_box(n->eqn->first, indent + 4);
	if (n->child)
		print_man(n->child, indent +
		    (n->type == ROFFT_BLOCK ? 2 : 4));
	if (n->next)
		print_man(n->next, indent);
}
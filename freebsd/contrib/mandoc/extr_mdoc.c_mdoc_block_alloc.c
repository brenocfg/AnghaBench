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
typedef  union mdoc_data {int dummy; } mdoc_data ;
struct roff_node {int /*<<< orphan*/  norm; struct mdoc_arg* args; } ;
struct roff_man {int /*<<< orphan*/  next; } ;
struct mdoc_arg {int /*<<< orphan*/  refcnt; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;

/* Variables and functions */
#define  MDOC_Bd 132 
#define  MDOC_Bf 131 
#define  MDOC_Bl 130 
#define  MDOC_En 129 
#define  MDOC_Rs 128 
 int /*<<< orphan*/  ROFFT_BLOCK ; 
 int /*<<< orphan*/  ROFF_NEXT_CHILD ; 
 int /*<<< orphan*/  mandoc_calloc (int,int) ; 
 struct roff_node* roff_node_alloc (struct roff_man*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roff_node_append (struct roff_man*,struct roff_node*) ; 

struct roff_node *
mdoc_block_alloc(struct roff_man *mdoc, int line, int pos,
    enum roff_tok tok, struct mdoc_arg *args)
{
	struct roff_node *p;

	p = roff_node_alloc(mdoc, line, pos, ROFFT_BLOCK, tok);
	p->args = args;
	if (p->args)
		(args->refcnt)++;

	switch (tok) {
	case MDOC_Bd:
	case MDOC_Bf:
	case MDOC_Bl:
	case MDOC_En:
	case MDOC_Rs:
		p->norm = mandoc_calloc(1, sizeof(union mdoc_data));
		break;
	default:
		break;
	}
	roff_node_append(mdoc, p);
	mdoc->next = ROFF_NEXT_CHILD;
	return p;
}
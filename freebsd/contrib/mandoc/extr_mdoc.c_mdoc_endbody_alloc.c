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
struct roff_node {int /*<<< orphan*/  end; int /*<<< orphan*/  norm; struct roff_node* body; TYPE_1__* parent; int /*<<< orphan*/  flags; } ;
struct roff_man {int /*<<< orphan*/  next; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDBODY_SPACE ; 
 int /*<<< orphan*/  NODE_ENDED ; 
 int /*<<< orphan*/  ROFFT_BODY ; 
 int /*<<< orphan*/  ROFF_NEXT_SIBLING ; 
 struct roff_node* roff_node_alloc (struct roff_man*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roff_node_append (struct roff_man*,struct roff_node*) ; 

struct roff_node *
mdoc_endbody_alloc(struct roff_man *mdoc, int line, int pos,
    enum roff_tok tok, struct roff_node *body)
{
	struct roff_node *p;

	body->flags |= NODE_ENDED;
	body->parent->flags |= NODE_ENDED;
	p = roff_node_alloc(mdoc, line, pos, ROFFT_BODY, tok);
	p->body = body;
	p->norm = body->norm;
	p->end = ENDBODY_SPACE;
	roff_node_append(mdoc, p);
	mdoc->next = ROFF_NEXT_SIBLING;
	return p;
}
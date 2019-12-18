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
struct roff_node {int flags; int /*<<< orphan*/  string; } ;
struct roff_man {int /*<<< orphan*/  next; int /*<<< orphan*/  roff; } ;

/* Variables and functions */
 int NODE_ENDED ; 
 int NODE_VALID ; 
 int /*<<< orphan*/  ROFFT_TEXT ; 
 int /*<<< orphan*/  ROFF_NEXT_SIBLING ; 
 int /*<<< orphan*/  TOKEN_NONE ; 
 struct roff_node* roff_node_alloc (struct roff_man*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_node_append (struct roff_man*,struct roff_node*) ; 
 int /*<<< orphan*/  roff_strdup (int /*<<< orphan*/ ,char const*) ; 

void
roff_word_alloc(struct roff_man *man, int line, int pos, const char *word)
{
	struct roff_node	*n;

	n = roff_node_alloc(man, line, pos, ROFFT_TEXT, TOKEN_NONE);
	n->string = roff_strdup(man->roff, word);
	roff_node_append(man, n);
	n->flags |= NODE_VALID | NODE_ENDED;
	man->next = ROFF_NEXT_SIBLING;
}
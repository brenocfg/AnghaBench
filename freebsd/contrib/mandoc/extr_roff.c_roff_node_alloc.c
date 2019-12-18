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
struct roff_node {int line; int pos; int tok; int type; int /*<<< orphan*/  flags; int /*<<< orphan*/  sec; } ;
struct roff_man {int flags; int /*<<< orphan*/  lastsec; } ;
typedef  enum roff_type { ____Placeholder_roff_type } roff_type ;

/* Variables and functions */
 int MDOC_NEWLINE ; 
 int MDOC_SYNOPSIS ; 
 int /*<<< orphan*/  NODE_LINE ; 
 int /*<<< orphan*/  NODE_NOFILL ; 
 int /*<<< orphan*/  NODE_SYNPRETTY ; 
 int ROFF_NOFILL ; 
 int ROFF_NONOFILL ; 
 struct roff_node* mandoc_calloc (int,int) ; 

struct roff_node *
roff_node_alloc(struct roff_man *man, int line, int pos,
	enum roff_type type, int tok)
{
	struct roff_node	*n;

	n = mandoc_calloc(1, sizeof(*n));
	n->line = line;
	n->pos = pos;
	n->tok = tok;
	n->type = type;
	n->sec = man->lastsec;

	if (man->flags & MDOC_SYNOPSIS)
		n->flags |= NODE_SYNPRETTY;
	else
		n->flags &= ~NODE_SYNPRETTY;
	if ((man->flags & (ROFF_NOFILL | ROFF_NONOFILL)) == ROFF_NOFILL)
		n->flags |= NODE_NOFILL;
	else
		n->flags &= ~NODE_NOFILL;
	if (man->flags & MDOC_NEWLINE)
		n->flags |= NODE_LINE;
	man->flags &= ~MDOC_NEWLINE;

	return n;
}
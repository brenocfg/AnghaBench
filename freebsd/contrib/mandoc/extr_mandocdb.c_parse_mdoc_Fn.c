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
typedef  int /*<<< orphan*/  uint64_t ;
struct roff_node {scalar_t__ type; scalar_t__ sec; TYPE_1__* child; } ;
struct roff_meta {int dummy; } ;
struct mpage {int dummy; } ;
struct TYPE_2__ {struct roff_node* next; } ;

/* Variables and functions */
 scalar_t__ ROFFT_TEXT ; 
 scalar_t__ SEC_SYNOPSIS ; 
 int /*<<< orphan*/  TYPE_Fa ; 
 int /*<<< orphan*/  TYPE_Vt ; 
 int /*<<< orphan*/  parse_mdoc_fname (struct mpage*,TYPE_1__*) ; 
 int /*<<< orphan*/  putmdockey (struct mpage*,struct roff_node const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_mdoc_Fn(struct mpage *mpage, const struct roff_meta *meta,
	const struct roff_node *n)
{
	uint64_t mask;

	if (n->child == NULL)
		return 0;

	parse_mdoc_fname(mpage, n->child);

	n = n->child->next;
	if (n != NULL && n->type == ROFFT_TEXT) {
		mask = TYPE_Fa;
		if (n->sec == SEC_SYNOPSIS)
			mask |= TYPE_Vt;
		putmdockey(mpage, n, mask, 0);
	}

	return 0;
}
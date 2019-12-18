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
typedef  int /*<<< orphan*/  uint64_t ;
struct roff_node {int flags; scalar_t__ type; int /*<<< orphan*/  string; struct roff_node* child; struct roff_node* next; } ;
struct mpage {int dummy; } ;

/* Variables and functions */
 scalar_t__ ROFFT_TEXT ; 
 int /*<<< orphan*/  putkey (struct mpage const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
putmdockey(const struct mpage *mpage,
	const struct roff_node *n, uint64_t m, int taboo)
{

	for ( ; NULL != n; n = n->next) {
		if (n->flags & taboo)
			continue;
		if (NULL != n->child)
			putmdockey(mpage, n->child, m, taboo);
		if (n->type == ROFFT_TEXT)
			putkey(mpage, n->string, m);
	}
}
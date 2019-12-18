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
struct roff_node {scalar_t__ tok; int flags; int type; struct roff_node* child; struct roff_node* next; } ;
struct roff_meta {int dummy; } ;
struct mpage {int dummy; } ;
struct mdoc_handler {int taboo; int /*<<< orphan*/  mask; int /*<<< orphan*/  (* fp ) (struct mpage*,struct roff_meta const*,struct roff_node const*) ;} ;

/* Variables and functions */
 scalar_t__ MDOC_Dd ; 
 scalar_t__ MDOC_MAX ; 
#define  ROFFT_BLOCK 132 
#define  ROFFT_BODY 131 
#define  ROFFT_ELEM 130 
#define  ROFFT_HEAD 129 
#define  ROFFT_TAIL 128 
 scalar_t__ ROFF_MAX ; 
 scalar_t__ TOKEN_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct mdoc_handler* mdoc_handlers ; 
 int /*<<< orphan*/  putmdockey (struct mpage*,struct roff_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct mpage*,struct roff_meta const*,struct roff_node const*) ; 

__attribute__((used)) static void
parse_mdoc(struct mpage *mpage, const struct roff_meta *meta,
	const struct roff_node *n)
{
	const struct mdoc_handler *handler;

	for (n = n->child; n != NULL; n = n->next) {
		if (n->tok == TOKEN_NONE || n->tok < ROFF_MAX)
			continue;
		assert(n->tok >= MDOC_Dd && n->tok < MDOC_MAX);
		handler = mdoc_handlers + (n->tok - MDOC_Dd);
		if (n->flags & handler->taboo)
			continue;

		switch (n->type) {
		case ROFFT_ELEM:
		case ROFFT_BLOCK:
		case ROFFT_HEAD:
		case ROFFT_BODY:
		case ROFFT_TAIL:
			if (handler->fp != NULL &&
			    (*handler->fp)(mpage, meta, n) == 0)
				break;
			if (handler->mask)
				putmdockey(mpage, n->child,
				    handler->mask, handler->taboo);
			break;
		default:
			continue;
		}
		if (NULL != n->child)
			parse_mdoc(mpage, meta, n);
	}
}
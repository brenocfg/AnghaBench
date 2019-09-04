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
struct trailer_item {int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int if_missing; int where; } ;
struct arg_item {TYPE_1__ conf; } ;
typedef  enum trailer_where { ____Placeholder_trailer_where } trailer_where ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
#define  MISSING_ADD 129 
#define  MISSING_DO_NOTHING 128 
 int /*<<< orphan*/  after_or_end (int) ; 
 int /*<<< orphan*/  apply_item_command (int /*<<< orphan*/ *,struct arg_item*) ; 
 int /*<<< orphan*/  free_arg_item (struct arg_item*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct trailer_item* trailer_from_arg (struct arg_item*) ; 

__attribute__((used)) static void apply_arg_if_missing(struct list_head *head,
				 struct arg_item *arg_tok)
{
	enum trailer_where where;
	struct trailer_item *to_add;

	switch (arg_tok->conf.if_missing) {
	case MISSING_DO_NOTHING:
		free_arg_item(arg_tok);
		break;
	case MISSING_ADD:
		where = arg_tok->conf.where;
		apply_item_command(NULL, arg_tok);
		to_add = trailer_from_arg(arg_tok);
		if (after_or_end(where))
			list_add_tail(&to_add->list, head);
		else
			list_add(&to_add->list, head);
		break;
	default:
		BUG("trailer.c: unhandled value %d",
		    arg_tok->conf.if_missing);
	}
}
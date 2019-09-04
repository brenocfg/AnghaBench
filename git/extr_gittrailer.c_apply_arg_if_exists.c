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
struct TYPE_2__ {int if_exists; } ;
struct arg_item {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
#define  EXISTS_ADD 132 
#define  EXISTS_ADD_IF_DIFFERENT 131 
#define  EXISTS_ADD_IF_DIFFERENT_NEIGHBOR 130 
#define  EXISTS_DO_NOTHING 129 
#define  EXISTS_REPLACE 128 
 int /*<<< orphan*/  add_arg_to_input_list (struct trailer_item*,struct arg_item*) ; 
 int /*<<< orphan*/  apply_item_command (struct trailer_item*,struct arg_item*) ; 
 int /*<<< orphan*/  check_if_different (struct trailer_item*,struct arg_item*,int,struct list_head*) ; 
 int /*<<< orphan*/  free_arg_item (struct arg_item*) ; 
 int /*<<< orphan*/  free_trailer_item (struct trailer_item*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apply_arg_if_exists(struct trailer_item *in_tok,
				struct arg_item *arg_tok,
				struct trailer_item *on_tok,
				struct list_head *head)
{
	switch (arg_tok->conf.if_exists) {
	case EXISTS_DO_NOTHING:
		free_arg_item(arg_tok);
		break;
	case EXISTS_REPLACE:
		apply_item_command(in_tok, arg_tok);
		add_arg_to_input_list(on_tok, arg_tok);
		list_del(&in_tok->list);
		free_trailer_item(in_tok);
		break;
	case EXISTS_ADD:
		apply_item_command(in_tok, arg_tok);
		add_arg_to_input_list(on_tok, arg_tok);
		break;
	case EXISTS_ADD_IF_DIFFERENT:
		apply_item_command(in_tok, arg_tok);
		if (check_if_different(in_tok, arg_tok, 1, head))
			add_arg_to_input_list(on_tok, arg_tok);
		else
			free_arg_item(arg_tok);
		break;
	case EXISTS_ADD_IF_DIFFERENT_NEIGHBOR:
		apply_item_command(in_tok, arg_tok);
		if (check_if_different(on_tok, arg_tok, 0, head))
			add_arg_to_input_list(on_tok, arg_tok);
		else
			free_arg_item(arg_tok);
		break;
	default:
		BUG("trailer.c: unhandled value %d",
		    arg_tok->conf.if_exists);
	}
}
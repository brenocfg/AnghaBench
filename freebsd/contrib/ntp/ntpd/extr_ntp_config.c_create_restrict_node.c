#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {short ippeerlimit; int line_no; int /*<<< orphan*/ * flag_tok_fifo; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * addr; } ;
typedef  TYPE_1__ restrict_node ;
typedef  int /*<<< orphan*/  int_fifo ;
typedef  int /*<<< orphan*/  address_node ;

/* Variables and functions */
 TYPE_1__* emalloc_zero (int) ; 

restrict_node *
create_restrict_node(
	address_node *	addr,
	address_node *	mask,
	short		ippeerlimit,
	int_fifo *	flag_tok_fifo,
	int		line_no
	)
{
	restrict_node *my_node;

	my_node = emalloc_zero(sizeof(*my_node));
	my_node->addr = addr;
	my_node->mask = mask;
	my_node->ippeerlimit = ippeerlimit;
	my_node->flag_tok_fifo = flag_tok_fifo;
	my_node->line_no = line_no;

	return my_node;
}
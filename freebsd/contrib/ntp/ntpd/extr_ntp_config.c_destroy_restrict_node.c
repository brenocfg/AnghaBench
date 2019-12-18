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
struct TYPE_4__ {int /*<<< orphan*/  flag_tok_fifo; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ restrict_node ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_address_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_int_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
destroy_restrict_node(
	restrict_node *my_node
	)
{
	/* With great care, free all the memory occupied by
	 * the restrict node
	 */
	destroy_address_node(my_node->addr);
	destroy_address_node(my_node->mask);
	destroy_int_fifo(my_node->flag_tok_fifo);
	free(my_node);
}
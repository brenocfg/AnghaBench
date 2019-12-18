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
struct TYPE_4__ {int filegen_token; int /*<<< orphan*/ * options; } ;
typedef  TYPE_1__ filegen_node ;
typedef  int /*<<< orphan*/  attr_val_fifo ;

/* Variables and functions */
 TYPE_1__* emalloc_zero (int) ; 

filegen_node *
create_filegen_node(
	int		filegen_token,
	attr_val_fifo *	options
	)
{
	filegen_node *my_node;

	my_node = emalloc_zero(sizeof(*my_node));
	my_node->filegen_token = filegen_token;
	my_node->options = options;

	return my_node;
}
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
struct TYPE_4__ {int /*<<< orphan*/ * servers; int /*<<< orphan*/ * init_opts; } ;
typedef  TYPE_1__ sim_node ;
typedef  int /*<<< orphan*/  server_info_fifo ;
typedef  int /*<<< orphan*/  attr_val_fifo ;

/* Variables and functions */
 TYPE_1__* emalloc (int) ; 

sim_node *
create_sim_node(
	attr_val_fifo *		init_opts,
	server_info_fifo *	servers
	)
{
	sim_node *my_node;

	my_node = emalloc(sizeof(*my_node));
	my_node->init_opts = init_opts;
	my_node->servers = servers;

	return my_node;
}